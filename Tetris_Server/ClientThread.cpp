//---------------------------------------------------------------------------

#pragma hdrstop

#include "ClientThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall ClientThread::ClientThread(SOCKET *_p_socket, CLIENTINFO _info) {
	m_eThreadWork = THREAD_STOP;
	Priority = tpTimeCritical;
	memset(&info, 0, sizeof(info));
	memcpy(&info, &_info, sizeof(info));
	data.ClientInfo = info;
	mp_socket = _p_socket;
	m_eThreadWork = THREAD_RUNNING;
}
//---------------------------------------------------------------------------

__fastcall ClientThread::~ClientThread() {
	UnicodeString tempStr = L"";
	tempStr.sprintf(L"[%d]Client Thread Terminated (from thread message)", info.ClientIndex);
	SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
}
//---------------------------------------------------------------------------

void __fastcall ClientThread::Execute() {

	// Common
	UnicodeString tempStr = L"";
	int t_ClientIdx = 0;
	int t_RecvErrorCnt = 0;

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

		// TCP Receive Routine
		if(Receive() == false) {
			tempStr.sprintf(L"Client [%d] is disconnected", data.ClientInfo.ClientIndex);
			SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
			m_eThreadWork = THREAD_TERMINATED;
			return;
		}

		WaitForSingleObject((void*)this->Handle, 50);
	}
	m_eThreadWork = THREAD_TERMINATED;
}
//---------------------------------------------------------------------------

void __fastcall ClientThread::Stop() {
	m_eThreadWork = THREAD_STOP;
}
//---------------------------------------------------------------------------

void __fastcall ClientThread::Resume() {
	m_eThreadWork = THREAD_RUNNING;
}
//---------------------------------------------------------------------------

void __fastcall ClientThread::DoTerminate() {

	if(*mp_socket != INVALID_SOCKET) {
		closesocket(*mp_socket);
		*mp_socket = INVALID_SOCKET;
	}

	m_eThreadWork = THREAD_TERMINATED;
}
//---------------------------------------------------------------------------

ThreadWorkingType __fastcall ClientThread::GetThreadStatus() {
	return m_eThreadWork;
}
//---------------------------------------------------------------------------

bool __fastcall ClientThread::Receive() {

	// Common
	UnicodeString tempStr = L"";
	int t_recvSize = 0;
	int t_CurrentSize = 0;
	BYTE t_SecureCode;
	unsigned short t_PacketSize = 0;
	BYTE t_MessageType = 0;

	// Reset Buffer
	memset(m_RecvBuff, 0, sizeof(m_RecvBuff));
	memset(data.Data, 0, sizeof(data.Data));

	// Receive Secure Code
	t_recvSize = recv(*mp_socket, (char*)&t_SecureCode, 1, 0);
	t_CurrentSize += t_recvSize;

	// Check Connection
	if(t_recvSize == 0 || t_recvSize == -1) return false;

	// Check Secure Code
	if(t_SecureCode != SECURE_CODE_C_TO_S) {
		tempStr.sprintf(L"Secure Code Incorrect");
		SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
		return false;
	}

	// Input Secure Code Into Buffer
	m_RecvBuff[0] = t_SecureCode;

	// Check Connection
	if(t_recvSize == 0 || t_recvSize == -1) return false;

	// Check Data Size
	t_recvSize = recv(*mp_socket, (char*)&t_PacketSize, 2, 0);
	t_CurrentSize += t_recvSize;

	// Check Connection
	if(t_recvSize == 0 || t_recvSize == -1) return false;

	// Input Data Size Into Buffer
	memcpy(&m_RecvBuff[1], &t_PacketSize, 2);

	// Check Message Type
	t_recvSize = recv(*mp_socket, (char*)&t_MessageType, 1, 0);
	t_CurrentSize += t_recvSize;

	// Check Connection
	if(t_recvSize == 0 || t_recvSize == -1) return false;

	// Input Message Type Into Buffer
	m_RecvBuff[3] = t_MessageType;

	// Receive Data Routine
	while(t_CurrentSize != t_PacketSize) {
		t_recvSize = recv(*mp_socket, (char*)(m_RecvBuff + t_CurrentSize), t_PacketSize - t_CurrentSize, 0);

		// Check Connection
		if(t_recvSize == 0 || t_recvSize == -1) return false;

		// Set Current Size
		t_CurrentSize += t_recvSize;
	}

	// Send a Proper Message To Main Thread.
	memcpy(data.Data, m_RecvBuff, MAX_RECV_PACKET_SIZE);
	SendMessage(FormMain->Handle, MSG_CLIENT_MESSAGE, (unsigned int)&data, 0x10);

	return true;
}
//---------------------------------------------------------------------------


