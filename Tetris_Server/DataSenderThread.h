//---------------------------------------------------------------------------

#ifndef DataSenderThreadH
#define DataSenderThreadH
//---------------------------------------------------------------------------

#include "Main.h"


class ThreadPool {
public:
	ThreadPool(size_t num_threads);
	~ThreadPool();

	void __fastcall EnqueueJob(std::function<void()> job);

private:
	size_t num_threads_;
	std::vector<std::thread> worker_threads_;
	std::queue<std::function<void()>> jobs_;
	std::condition_variable cv_job_q_;
	std::mutex m_job_q_;

	bool stop_all;

	void WorkerThread();
};


class DataSenderThread : public TThread {
private:
	ThreadWorkingType	m_eThreadWork;
	SOCKET* mp_socket;
	CLIENTINFO info;
	CLIENTMSG data;
	std::mutex* p_mutex_ClientMsgQ;
	std::condition_variable* p_cv;
	int iSenderID;

public:
	DataSenderThread(int _iID, std::mutex* _p_mutex, std::condition_variable* _p_cv);
	~DataSenderThread();

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
