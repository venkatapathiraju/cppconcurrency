#include <iostream>
#include <thread>



int main(int argc, char *argv[])
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