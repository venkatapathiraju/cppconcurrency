

#include <mutex>
#include <thread>
/*
A condition variable is a synchronization primitive that provides a queue for threads waiting for a resource.
First step is for the thread to test if the resource is variable.
If available use it. If not, then add itself to the queue of threads waiting for the resource.
When the thread is finished with the resource, it wakes up exactly one thread from the queue.
*/

namespace condition_variable
{
	std::mutex mut;
	std::condition_variable cv;
	bool bready = false;
	std::string str = "hello";

	void worker_thread()
	{
		std::unique_lock<std::mutex> lk(mut);
		cv.wait(lk, []() { return bready; });
		str = "hi";
		lk.unlock();
		cv.notify_one();
	}



	void cvtest()
	{
		std::thread wt(worker_thread);
		
		std::cout << "Begin conditional variable exercise" << std::endl;
		{
			std::lock_guard<std::mutex> lg(mut);
			bready = true;
		}
		cv.notify_one();
		std::cout << str << std::endl;

		wt.join();

	}
}