//---------------------------------------------------------------------------

#ifndef ClientThreadH
#define ClientThreadH
//---------------------------------------------------------------------------

#include "Main.h"


class ClientThread : public TThread {
private:
	ThreadWorkingType	m_eThreadWork;
	SOCKET* mp_socket;
	//BYTE m_RecvBuff[MAX_RECV_PACKET_SIZE] = {0, };
	BYTE m_RecvBuff[MAX_RECV_PACKET_SIZE];

public:
	CLIENTINFO info;
	CLIENTMSG data;

public:
	__fastcall ClientThread(SOCKET *_p_socket, CLIENTINFO _info);
	__fastcall ~ClientThread();

    bool __fastcall Receive();

	void __fastcall Execute();
	void __fastcall Stop();
	void __fastcall Resume();
	void __fastcall DoTerminate();
	ThreadWorkingType __fastcall GetThreadStatus();
};
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
#endif
