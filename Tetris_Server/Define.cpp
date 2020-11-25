//---------------------------------------------------------------------------

#pragma hdrstop

#include "Define.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall CTCPListenThread::CTCPListenThread() {
	m_eThreadWork = THREAD_STOP;
	Priority = tpTimeCritical;
	m_StartTime = Now();
	m_CurrentTime = m_StartTime;
	m_msg = L"";

	// Socket Create
	if(Create() == false) {
		DoTerminate();
	} else {
		m_eThreadWork = THREAD_RUNNING;
	}
}
//---------------------------------------------------------------------------

__fastcall CTCPListenThread::~CTCPListenThread() {
	if(m_socket_TCP != INVALID_SOCKET) {
		closesocket(m_socket_TCP);
		m_socket_TCP = NULL;
		m_msg = L"Socket delete success";
	}
}
//---------------------------------------------------------------------------

bool __fastcall CTCPListenThread::Create() {
	// Create Listen Socket
	m_socket_TCP = socket(AF_INET, SOCK_STREAM, 0);
	if(m_socket_TCP == INVALID_SOCKET) {
		m_msg = L"Socket create fail";
		return false;
	}

	memset(&m_sockaddr_in, 0, sizeof(m_sockaddr_in));
	m_sockaddr_in.sin_family = AF_INET;
	m_sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	m_sockaddr_in.sin_port = htons(TCP_SERVER_PORT);

	int t_SockOpt = 1;
	setsockopt(m_socket_TCP, SOL_SOCKET, SO_REUSEADDR, (char*)&t_SockOpt, sizeof(t_SockOpt));
	if(bind(m_socket_TCP, (struct sockaddr*)&m_sockaddr_in, sizeof(m_sockaddr_in)) < 0) {
		m_msg = L"Socket bind fail";
		return false;
	}

	if(listen(m_socket_TCP, MAX_TCP_CLIENT_LISTENING_COUNT) < 0) {
		m_msg = L"Socket Listen Fail";
		return false;
	}

	m_msg = L"Socket is ready";
	return true;
}
//---------------------------------------------------------------------------

void __fastcall CTCPListenThread::Execute() {

	// Common
	UnicodeString t_Str = L"";
	SOCKET t_Socket = INVALID_SOCKET;
	struct sockaddr_in	t_client_sockaddr_in;
	memset(&t_client_sockaddr_in, 0, sizeof(t_client_sockaddr_in));
	int t_len = sizeof(t_client_sockaddr_in);


	while(!Terminated) {
		if(m_eThreadWork != THREAD_RUNNING) {
			if(m_eThreadWork == THREAD_TERMINATED) break;
			WaitForSingleObject((void*)this->Handle, 500);
			continue;
		}
		m_CurrentTime = IncSecond(m_CurrentTime, 1);
		t_Str = m_CurrentTime.TimeString() + L" ";
		SendMessage(FormMain->Handle, MYMSG, (unsigned int)&t_Str, 0x10);

		t_Socket = accept(m_socket_TCP, (struct sockaddr*)&t_client_sockaddr_in, &t_len);

		if(t_Socket != INVALID_SOCKET) {
			t_Str = L"WELCOME ";
			SendMessage(FormMain->Handle, MYMSG, (unsigned int)&t_Str, 0x10);
		}


		WaitForSingleObject((void*)this->Handle, 1000);
	}
	m_eThreadWork = THREAD_TERMINATED;
}
//---------------------------------------------------------------------------

void __fastcall CTCPListenThread::Stop() {
	m_eThreadWork = THREAD_STOP;
}
//---------------------------------------------------------------------------

void __fastcall CTCPListenThread::Resume() {
	m_eThreadWork = THREAD_RUNNING;
}
//---------------------------------------------------------------------------

void __fastcall CTCPListenThread::DoTerminate() {
	m_eThreadWork = THREAD_TERMINATED;
	if(m_socket_TCP != INVALID_SOCKET) {
		closesocket(m_socket_TCP);
		m_socket_TCP = NULL;
		m_msg = L"Socket delete success";
	}
}
//---------------------------------------------------------------------------

ThreadWorkingType __fastcall CTCPListenThread::GetThreadStatus() {
	return m_eThreadWork;
}
//---------------------------------------------------------------------------

TTime __fastcall CTCPListenThread::GetStartTime() {
	return m_StartTime;
}
//---------------------------------------------------------------------------

TTime __fastcall CTCPListenThread::GetCurrentTime() {
	return m_CurrentTime;
}
//---------------------------------------------------------------------------
