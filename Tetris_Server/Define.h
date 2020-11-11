//---------------------------------------------------------------------------

#ifndef DefineH
#define DefineH
//---------------------------------------------------------------------------


#include "Main.h"
//#include <System.Classes.hpp>
//#include <winsock2.h>

enum ThreadWorkingType
{
	THREAD_STOP = 0,
	THREAD_RUNNING = 1,
	THREAD_TERMINATED = 2,
};
//---------------------------------------------------------------------------

class CTCPListenThread : public TThread {
private:
	ThreadWorkingType	m_eThreadWork;
	SOCKET	m_sock_TCP;
	struct sockaddr_in	m_sockaddr_in;
	TTime m_StartTime;
	TTime m_CurrentTime;

protected:
public:
	//FormMain->
	//extern PACKAGE TFormMain *FormMain;
	__fastcall CTCPListenThread();
	void __fastcall Execute();
	void __fastcall Stop();
	void __fastcall Resume();
	void __fastcall DoTerminate();
	ThreadWorkingType __fastcall GetThreadStatus();
	TTime __fastcall GetStartTime();
	TTime __fastcall GetCurrentTime();
};
//---------------------------------------------------------------------------


#endif
