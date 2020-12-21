//---------------------------------------------------------------------------

#ifndef TCPListenThreadH
#define TCPListenThreadH
//---------------------------------------------------------------------------

#include "Main.h"



class CTCPListenThread : public TThread {
private:
	ThreadWorkingType	m_eThreadWork;
	SOCKET* mp_socket_TCP;
	SOCKET* mp_ClientSocket;
	int* m_pClientCnt;
	struct sockaddr_in	m_sockaddr_in;
	TDateTime m_ConnectionDateTime;

	int m_bindrst;

protected:
public:
	__fastcall CTCPListenThread(SOCKET *_p_socket, SOCKET* _p_clientsocket, int* _p_clientcount);
	__fastcall ~CTCPListenThread();
	void __fastcall Execute();
	void __fastcall Stop();
	void __fastcall Resume();
	void __fastcall DoTerminate();
	ThreadWorkingType __fastcall GetThreadStatus();
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
#endif
