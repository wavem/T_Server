//---------------------------------------------------------------------------

#ifndef DataSenderThreadH
#define DataSenderThreadH
//---------------------------------------------------------------------------

#include "Main.h"

class DataSenderThread : public TThread {
private:
	ThreadWorkingType	m_eThreadWork;
	SOCKET* mp_socket;
	SERVERMSG ServerMsg;
	//std::mutex* p_mutex_ClientMsgQ;
	//std::condition_variable* p_cv;
	int iSenderID;
	HANDLE Mutex;

public:
	//DataSenderThread(int _iID, std::mutex* _p_mutex, std::condition_variable* _p_cv);
	DataSenderThread(int _iID, HANDLE _Mutex);
	__fastcall ~DataSenderThread();

	bool __fastcall Send();
	void __fastcall Execute();
	void __fastcall Stop();
	void __fastcall Resume();
	void __fastcall DoTerminate();
	ThreadWorkingType __fastcall GetThreadStatus();
};
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
#endif
