//---------------------------------------------------------------------------

#pragma hdrstop

#include "TCPListenThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall CTCPListenThread::CTCPListenThread(SOCKET *_p_socket, SOCKET* _p_clientsocket, int* _p_clientcount) {
	m_eThreadWork = THREAD_STOP;
	Priority = tpTimeCritical;
	mp_socket_TCP = _p_socket;
	mp_ClientSocket = _p_clientsocket;
	m_ClientCnt = _p_clientcount;

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
	SOCKET* tp_Socket = NULL;
	int t_ClientIdx = 0;

	CLIENTINFO t_ClientInfo;
	struct sockaddr_in t_client_sockaddr_in;
	memset(&t_client_sockaddr_in, 0, sizeof(t_client_sockaddr_in));
	int t_len = sizeof(t_client_sockaddr_in);


	while(!Terminated) {
		// For Thread Stop & Resume
		if(m_eThreadWork != THREAD_RUNNING) {
			if(m_eThreadWork == THREAD_TERMINATED) break;
			WaitForSingleObject((void*)this->Handle, 500);
			continue;
		}

		// Find Empty Socket
		for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
			if(*(mp_ClientSocket + i) == INVALID_SOCKET) {
				tp_Socket = (mp_ClientSocket + i);
				t_ClientIdx = i; // For Throwing to Main Class
				i = MAX_TCP_CLIENT_USER_COUNT; // For Breaking For Loop...
				continue;
			}
		}

		// Check Connected Client Count
		if(*m_ClientCnt >= 60) {
			WaitForSingleObject((void*)this->Handle, 500);
			continue;
		}

		// Accept Routine
		*tp_Socket = accept(*mp_socket_TCP, (struct sockaddr*)&t_client_sockaddr_in, &t_len);

		if(*tp_Socket != INVALID_SOCKET) {

			// Time Calculation
			m_ConnectionDateTime = Now();

			// Making Client Information
			t_ClientInfo.ClientIndex = t_ClientIdx;
			t_ClientInfo.ConnectionDateTime = m_ConnectionDateTime;
			t_ClientInfo.ClientSockAddrIn = t_client_sockaddr_in;

			// Print Welcome Message
			tempStr.sprintf(L"WELCOME, Client [%d] ", t_ClientIdx);
			tempStr += m_ConnectionDateTime.DateTimeString() + L" ";
			SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);

			// Send Message : Do Create Client Thread !!
			SendMessage(FormMain->Handle, MSG_NEW_CONNECTION, (unsigned int)&t_ClientInfo, 0x01);

			// Reset Client Sock Addr
			memset(&t_client_sockaddr_in, 0, sizeof(t_client_sockaddr_in));
			t_len = sizeof(t_client_sockaddr_in);

			// Reset Client Information Structure
			memset(&t_ClientInfo, 0, sizeof(t_ClientInfo));
		}

		WaitForSingleObject((void*)this->Handle, 100);
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
