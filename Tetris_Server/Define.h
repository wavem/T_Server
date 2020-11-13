//---------------------------------------------------------------------------

#ifndef DefineH
#define DefineH
//---------------------------------------------------------------------------


#include "Main.h"
//#include <System.Classes.hpp>
//#include <winsock2.h>

#define TCP_SERVER_PORT		14759
#define MAX_TCP_CLIENT_LISTENING_COUNT	10
#define MAX_TCP_CLIENT_USER_COUNT		60

// Message Define


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
	SOCKET	m_socket_TCP;
	struct sockaddr_in	m_sockaddr_in;
	TTime m_StartTime;
	TTime m_CurrentTime;
	int m_bindrst;

protected:
public:
	UnicodeString m_msg;
	__fastcall CTCPListenThread();
	__fastcall ~CTCPListenThread();
	bool __fastcall Create();
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
