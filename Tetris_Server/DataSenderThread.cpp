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

		WaitForSingleObject(Mutex, INFINITE);
		if(FormMain->m_ClientMsgQ.empty()) {
			ReleaseMutex(Mutex);
			continue;
		}

		data = FormMain->m_ClientMsgQ.front();
		FormMain->m_ClientMsgQ.pop();
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
	t_MessageType = data.Data[3];

	// Extract Packet Size
	memcpy(&t_PacketSize, &data.Data[1], 2);

	// Send Routine
	switch(t_MessageType) {
	case DATA_TYPE_SIGN_UP:
		t_rst = 0;
		t_rst = send(FormMain->m_ClientSocket[data.ClientInfo.ClientIndex], (char*)data.Data, t_PacketSize, 0);
		break;
	case DATA_TYPE_SIGN_IN:
		t_rst = 0;
		t_rst = send(FormMain->m_ClientSocket[data.ClientInfo.ClientIndex], (char*)data.Data, t_PacketSize, 0);
		break;
	case DATA_TYPE_LOBBY_CHATTING:
		for(int i = 0 ; i < MAX_TCP_CLIENT_USER_COUNT ; i++) {
			if(FormMain->m_ClientSocket[i] != INVALID_SOCKET) {
				t_rst = 0;
				t_rst = send(FormMain->m_ClientSocket[i], (char*)data.Data, t_PacketSize, 0);
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
