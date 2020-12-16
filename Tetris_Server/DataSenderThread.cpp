//---------------------------------------------------------------------------

#pragma hdrstop

#include "DataSenderThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

DataSenderThread::DataSenderThread(int _iID, HANDLE _Mutex) {
	m_eThreadWork = THREAD_STOP;
	Priority = tpTimeCritical;
	Mutex = _Mutex;
	iSenderID = _iID;

	m_eThreadWork = THREAD_RUNNING;
}
//---------------------------------------------------------------------------

__fastcall DataSenderThread::~DataSenderThread() {
	UnicodeString tempStr = L"";
	tempStr.sprintf(L"[%d]Data Sender Thread Terminated (from thread message)", iSenderID);
	SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
}
//---------------------------------------------------------------------------

void __fastcall DataSenderThread::Execute() {

	// Common
	UnicodeString tempStr = L"";
	int temp = 0;

	while(!Terminated) {
		// For Thread Stop & Resume
		if(m_eThreadWork != THREAD_RUNNING) {
			if(m_eThreadWork == THREAD_TERMINATED) break;
			WaitForSingleObject((void*)this->Handle, 200);
			continue;
		}

		// Reset Send Buffer Memory
		memset(&ServerMsg, 0, sizeof(ServerMsg));

		WaitForSingleObject(Mutex, INFINITE);
		if(FormMain->m_ServerMsgQ.empty()) {
			ReleaseMutex(Mutex);
			continue;
		}

		ServerMsg = FormMain->m_ServerMsgQ.front();
		FormMain->m_ServerMsgQ.pop();
		FormMain->m_SenderThreadWorkCount[iSenderID]++;
		ReleaseMutex(Mutex);

		// Send Routine
		if(Send()) {

		} else {

		}
	}

	m_eThreadWork = THREAD_TERMINATED;
}
//---------------------------------------------------------------------------

bool __fastcall DataSenderThread::Send() {

	// Common
	UnicodeString tempStr = L"";
	int t_rst = 0;
	int t_MessageType = 0;
	unsigned short t_PacketSize = 0;

	// Extract Message Type
	t_MessageType = ServerMsg.Data[3];

	// Extract Packet Size
	memcpy(&t_PacketSize, &ServerMsg.Data[1], 2);

	// Send Routine
	switch(t_MessageType) {
	case DATA_TYPE_SIGN_UP:
		t_rst = 0;
		t_rst = send(FormMain->m_ClientSocket[ServerMsg.ClientInfo.ClientIndex], (char*)ServerMsg.Data, t_PacketSize, 0);
		break;
	case DATA_TYPE_SIGN_IN:
		t_rst = 0;
		t_rst = send(FormMain->m_ClientSocket[ServerMsg.ClientInfo.ClientIndex], (char*)ServerMsg.Data, t_PacketSize, 0);
		break;
	case DATA_TYPE_LOBBY_CHATTING:
	case DATA_TYPE_LOBBY_PLAYERLIST: // 굳이 게임중인 사람들한테는 안보내도 되긴 하지만, 귀찮으니 걍 보낸다.
		for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
			if(FormMain->m_ClientSocket[i] != INVALID_SOCKET) {
				t_rst = 0;
				t_rst = send(FormMain->m_ClientSocket[i], (char*)ServerMsg.Data, t_PacketSize, 0);
			}
		}
		break;

	default:
		break;
	}

	return true;
}
//---------------------------------------------------------------------------

void __fastcall DataSenderThread::Stop() {
	m_eThreadWork = THREAD_STOP;
}
//---------------------------------------------------------------------------

void __fastcall DataSenderThread::Resume() {
	m_eThreadWork = THREAD_RUNNING;
}
//---------------------------------------------------------------------------

void __fastcall DataSenderThread::DoTerminate() {
	m_eThreadWork = THREAD_TERMINATED;
}
//---------------------------------------------------------------------------

ThreadWorkingType __fastcall DataSenderThread::GetThreadStatus() {
	return m_eThreadWork;
}
//---------------------------------------------------------------------------
