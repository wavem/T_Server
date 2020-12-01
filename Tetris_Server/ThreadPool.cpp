//---------------------------------------------------------------------------

#pragma hdrstop

#include "ThreadPool.h"
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

		// �� ���� job �� ����.
		std::function<void()> job = std::move(jobs_.front());
		jobs_.pop();
		lock.unlock();

		// �ش� job �� �����Ѵ� :)
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
		throw std::runtime_error("ThreadPool ��� ������");
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

    // �� ���� job �� ����.
    std::function<void()> job = std::move(jobs_.front());
    jobs_.pop();
    lock.unlock();

    // �ش� job �� �����Ѵ� :)
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
	throw std::runtime_error("ThreadPool ��� ������");
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


