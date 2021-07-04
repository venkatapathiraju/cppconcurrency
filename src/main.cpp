#include <iostream>
#include <thread>
#include <chrono>
#include <future>


//Use futures, async, promise etc

int delayedaccumulator(int n)
{
	std::cout << "Begin of delayed accumulator" << std::endl;
	using namespace std::chrono_literals;
	int sum = 0;
	for(int i=0; i<=n ; i++)
	{
		std::this_thread::sleep_for(100ms);
		sum+=i;
	}
	std::cout << "End of delayed accumulator" << std::endl;
	return sum;
}

void basicthreadcall()
{
	auto sqr = [](int x) { 
		std::cout << "Square root of " << x << " is " << x*x << std::endl;
		return x*x; 
	};

	int cores = std::thread::hardware_concurrency();
	std::cout << "Hardware cores->" << cores;

	//Run the function with parallelism
	for(int i =0; i < 1000;i++)
	{
		std::thread t(sqr,i);
		t.join();
	}
}



int main(int argc, char *argv[])
{

	//call a function asynchronously
	auto result = std::async(delayedaccumulator,100);

	std::cout << " Do something else" << std::endl;
	std::cout << "Got the result " << result.get() << std::endl;
		

}