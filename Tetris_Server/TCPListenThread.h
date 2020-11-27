//---------------------------------------------------------------------------

#ifndef TCPListenThreadH
#define TCPListenThreadH
//---------------------------------------------------------------------------

#include "Main.h"



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
	SOCKET* mp_socket_TCP;
	struct sockaddr_in	m_sockaddr_in;
	TTime m_StartTime;
	TTime m_CurrentTime;
	int m_bindrst;

protected:
public:
	UnicodeString m_msg;
	//__fastcall CTCPListenThread();
	__fastcall CTCPListenThread(SOCKET *_p_socket);
	__fastcall ~CTCPListenThread();
	void __fastcall Execute();
	void __fastcall Stop();
	void __fastcall Resume();
	void __fastcall DoTerminate();
	ThreadWorkingType __fastcall GetThreadStatus();
	TTime __fastcall GetStartTime();
	TTime __fastcall GetCurrentTime();
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
