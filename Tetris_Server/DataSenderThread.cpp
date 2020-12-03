//---------------------------------------------------------------------------

#pragma hdrstop

#include "DataSenderThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


ThreadPool::ThreadPool(size_t num_threads)
 : num_threads_(num_threads), stop_all(false)
{
	worker_threads_.reserve(num_threads_);
	for (size_t i = 0; i < num_threads_; ++i) {
		worker_threads_.emplace_back([this]() { this->WorkerThread(); });
	}
}
//---------------------------------------------------------------------------

void ThreadPool::WorkerThread() {
	while (true) {
		std::unique_lock<std::mutex> lock(m_job_q_);
		cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
		if (stop_all && this->jobs_.empty()) {
			return;
		}

		// 맨 앞의 job 을 뺀다.
		std::function<void()> job = std::move(jobs_.front());
		jobs_.pop();
		lock.unlock();

		// 해당 job 을 수행한다 :)
		job();
	}
}
//---------------------------------------------------------------------------

ThreadPool::~ThreadPool() {
	stop_all = true;
	cv_job_q_.notify_all();

	for (auto& t : worker_threads_) {
		t.join();
	}
}
//---------------------------------------------------------------------------

void ThreadPool::EnqueueJob(std::function<void()> job) {
	if (stop_all) {
		throw std::runtime_error("ThreadPool 사용 중지됨");
	}
	{
		std::lock_guard<std::mutex> lock(m_job_q_);
		jobs_.push(std::move(job));
	}
	cv_job_q_.notify_one();
}
//---------------------------------------------------------------------------




/*

ThreadPool::ThreadPool(size_t num_threads)
    : num_threads_(num_threads), stop_all(false) {
  worker_threads_.reserve(num_threads_);
  for (size_t i = 0; i < num_threads_; ++i) {
    worker_threads_.emplace_back([this]() { this->WorkerThread(); });
  }
}

void ThreadPool::WorkerThread() {
  while (true) {
    std::unique_lock<std::mutex> lock(m_job_q_);
    cv_job_q_.wait(lock, [this]() { return !this->jobs_.empty() || stop_all; });
    if (stop_all && this->jobs_.empty()) {
      return;
    }

    // 맨 앞의 job 을 뺀다.
    std::function<void()> job = std::move(jobs_.front());
    jobs_.pop();
    lock.unlock();

    // 해당 job 을 수행한다 :)
    job();
  }
}

ThreadPool::~ThreadPool() {
  stop_all = true;
  cv_job_q_.notify_all();

  for (auto& t : worker_threads_) {
    t.join();
  }
}

void ThreadPool::EnqueueJob(std::function<void()> job) {
  if (stop_all) {
	throw std::runtime_error("ThreadPool 사용 중지됨");
  }
  {
    std::lock_guard<std::mutex> lock(m_job_q_);
    jobs_.push(std::move(job));
  }
  cv_job_q_.notify_one();
}

}  // namespace ThreadPool

void work(int t, int id) {
  printf("%d start \n", id);
  std::this_thread::sleep_for(std::chrono::seconds(t));
  printf("%d end after %ds\n", id, t);
}

int main() {
  ThreadPool::ThreadPool pool(3);

  for (int i = 0; i < 10; i++) {
	pool.EnqueueJob([i]() { work(i % 3 + 1, i); });
  }
}                    */



//---------------------------------------------------------------------------



DataSenderThread::DataSenderThread(SOCKET *_p_socket, CLIENTINFO _info) {
	m_eThreadWork = THREAD_STOP;
	Priority = tpTimeCritical;
	//memset(&info, 0, sizeof(info));
	//memcpy(&info, &_info, sizeof(info));


	mp_socket = _p_socket;

	m_eThreadWork = THREAD_RUNNING;
}
//---------------------------------------------------------------------------

DataSenderThread::~DataSenderThread() {
	UnicodeString tempStr = L"";
	tempStr.sprintf(L"[%d]Client Thread Terminated (from thread message)", info.ClientIndex);
	SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
}
//---------------------------------------------------------------------------

void __fastcall DataSenderThread::Execute() {

	// Common
	UnicodeString tempStr = L"";
	int t_ClientIdx = 0;

	CLIENTINFO t_ClientInfo;
	struct sockaddr_in t_client_sockaddr_in;
	memset(&t_client_sockaddr_in, 0, sizeof(t_client_sockaddr_in));
	int t_len = sizeof(t_client_sockaddr_in);

	BYTE t_Buff[256] = {0, };
	int t_recvSize = 0;

	while(!Terminated) {
		// For Thread Stop & Resume
		if(m_eThreadWork != THREAD_RUNNING) {
			if(m_eThreadWork == THREAD_TERMINATED) break;
			WaitForSingleObject((void*)this->Handle, 500);
			continue;
		}

		// TCP Receive Routine
		t_recvSize = recv(*mp_socket, (char*)t_Buff, 256, 0);
		if(t_recvSize == 0 || t_recvSize == -1) {
			tempStr.sprintf(L"Client [%d] is disconnected", info.ClientIndex);
			SendMessage(FormMain->Handle, MSG_MEMO, (unsigned int)&tempStr, 0x10);
			m_eThreadWork = THREAD_TERMINATED;
			return;
		}

		// Time Calculation
		//m_ConnectionDateTime = Now();

		WaitForSingleObject((void*)this->Handle, 100);
	}
	m_eThreadWork = THREAD_TERMINATED;
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

	if(*mp_socket != INVALID_SOCKET) {
		closesocket(*mp_socket);
		*mp_socket = INVALID_SOCKET;
	}

	m_eThreadWork = THREAD_TERMINATED;
}
//---------------------------------------------------------------------------

ThreadWorkingType __fastcall DataSenderThread::GetThreadStatus() {
	return m_eThreadWork;
}
//---------------------------------------------------------------------------
