#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <memory>
#include <functional>

#include "conditionvariable.h"


//Use futures, async, promise etc
// async : async destructor blocks 
// packaged_task : communicates the return at the end of the function
// promise : the return .setvalue can be set in the middle of the callee function
// conditional_variable : synchronize the threads between each other by waiting, notifying 
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

int funcwithexception()
{
	std::cout << "Throwing exception " <<std::endl;
	throw std::runtime_error("Exception");
	return 0;
}


//Use async only when you don't care about the return type, because the return of async , i.e ~future blocks
void asynctest()
{


	//std::async(delayedaccumulator,50); // accumulates slowly
	auto f1 = std::async(delayedaccumulator,50); // accumulates slowly
	//std::async(funcwithexception); // returns exeption
	auto f2 = std::async(funcwithexception); // returns exeption


	std::cout << "Got the result " << f1.get() << std::endl;
		
	
	 try{
	 	std::cout << f2.get();	
	 }
	 catch(std::runtime_error ex){
	 	std::cout << ex.what() << std::endl;
	 }


}

void packagedtest()
{
	auto multiply = [](int a, int b){
		return a*b;
	};
	using Predicate = int(int,int);
	std::packaged_task<Predicate> task(multiply);
	std::future<int> result = task.get_future();
	task(2,9);
	std::cout << "Task lambda" << result.get();

	std::packaged_task<Predicate> task1(multiply);
	auto result1 = task1.get_future();
	std::thread t(std::move(task1),5,10);
	t.join();

	std::cout << "packaged task with thread " << result1.get() << std::endl; 

}





int main(int argc, char *argv[])
{
	condition_variable::cvtest();
	packagedtest();
	basicthreadcall();
	asynctest();
}