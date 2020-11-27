//---------------------------------------------------------------------------

#pragma hdrstop

#include "TCPListenThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall CTCPListenThread::CTCPListenThread(SOCKET *_p_socket) {
	m_eThreadWork = THREAD_STOP;
	Priority = tpTimeCritical;
	mp_socket_TCP = _p_socket;



	m_StartTime = Now();
	m_CurrentTime = m_StartTime;
	m_msg = L"";

	m_eThreadWork = THREAD_RUNNING;
}
//---------------------------------------------------------------------------

__fastcall CTCPListenThread::~CTCPListenThread() {
	UnicodeString tempStr = L"Listen Thread Terminated (from thread message)";
	SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
}
//---------------------------------------------------------------------------

void __fastcall CTCPListenThread::Execute() {

	// Common
	UnicodeString tempStr = L"";

	SOCKET t_Socket = INVALID_SOCKET;
	struct sockaddr_in	t_client_sockaddr_in;
	memset(&t_client_sockaddr_in, 0, sizeof(t_client_sockaddr_in));
	int t_len = sizeof(t_client_sockaddr_in);


	while(!Terminated) {
		// For Thread Stop & Resume
		if(m_eThreadWork != THREAD_RUNNING) {
			if(m_eThreadWork == THREAD_TERMINATED) break;
			WaitForSingleObject((void*)this->Handle, 500);
			continue;
		}

		// Time Calculation
		m_CurrentTime = IncSecond(m_CurrentTime, 1);
		tempStr = m_CurrentTime.TimeString() + L" ";
		SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);

		t_Socket = accept(*mp_socket_TCP, (struct sockaddr*)&t_client_sockaddr_in, &t_len);

		if(t_Socket != INVALID_SOCKET) {
			tempStr = L"WELCOME ";
			SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
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

	if(*mp_socket_TCP != INVALID_SOCKET) {
		closesocket(*mp_socket_TCP);
		*mp_socket_TCP = INVALID_SOCKET;
	}

	m_eThreadWork = THREAD_TERMINATED;
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
