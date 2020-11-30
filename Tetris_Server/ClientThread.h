//---------------------------------------------------------------------------

#ifndef ClientThreadH
#define ClientThreadH
//---------------------------------------------------------------------------

#include "Main.h"


class ClientThread : public TThread {
private:
	ThreadWorkingType	m_eThreadWork;
	SOCKET* mp_socket;

public:
	CLIENTINFO info;

public:
	__fastcall ClientThread(SOCKET *_p_socket, CLIENTINFO _info);
	__fastcall ~ClientThread();

	void __fastcall Execute();
	void __fastcall Stop();
	void __fastcall Resume();
	void __fastcall DoTerminate();
	ThreadWorkingType __fastcall GetThreadStatus();
};
//---------------------------------------------------------------------------







//---------------------------------------------------------------------------
#endif
