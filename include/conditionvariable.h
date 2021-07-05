

#include <mutex>
#include <thread>

namespace condition_variable
{
	std::mutex mut;
	std::condition_variable cv;
	bool bready = false;

	void worker_thread()
	{
		std::unique_lock<std::mutex> lk(mut);
		cv.wait(lk, []() { return bready; });
		lk.unlock();
		cv.notify_one();
	}



	void cvtest()
	{
		std::thread wt(worker_thread);
		

		std::cout << "Begin conditional variable exercise";
		{
			std::lock_guard<std::mutex> lg(mut);
			bready = true;
		}


		wt.join();

	}
}