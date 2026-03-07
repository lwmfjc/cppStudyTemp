#ifdef LY_EP62_

#include <iostream>
#include <thread>

void DoWork()
{
	while (true)
	{
		std::cout << "working..." << std::endl;
		//用户输入任何信息后继续执行
		std::cin.get();
	}
}

int main()
{ 
	std::thread worker(DoWork); 

	worker.join();

	//子线程完成前不会执行该行代码
	std::cin.get();
}
#endif