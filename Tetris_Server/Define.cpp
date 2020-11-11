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

	//m_socket_TCP
}
//---------------------------------------------------------------------------

void __fastcall CTCPListenThread::Execute() {

	// Common
	UnicodeString t_Str = L"";
	int t_Cnt = 0;

	m_eThreadWork = THREAD_RUNNING;
	while(!Terminated) {
		if(m_eThreadWork != THREAD_RUNNING) {
			if(m_eThreadWork == THREAD_TERMINATED) break;
			WaitForSingleObject((void*)this->Handle, 500);
			continue;
		}
		m_CurrentTime = IncSecond(m_CurrentTime, 1);
		//t_Str.sprintf(L"Thread Running Count : %d", t_Cnt++);
		//FormMain->PrintMsg(t_Str);
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
