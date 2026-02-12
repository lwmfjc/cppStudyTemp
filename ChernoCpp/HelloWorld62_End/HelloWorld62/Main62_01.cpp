#ifdef LY_EP62_

#include <iostream>
#include <thread>

class Test
{
public:
	Test()
	{
		std::cout << "Test()" << std::endl;
	}

	Test(int k)
	{
		std::cout << "Test(int)" << std::endl;
	}
};
void DoWork()
{

}

int main()
{
	//声明一个类Test的对象
	Test t{};

	// 这是一个函数声明，声明一个函数名
	// 为 t1，没有参数，返回类型
	// 是 Test
	Test t1();

	// 这是一个函数声明，声明一个函数名
	// 为 worker，没有参数，返回类型
	// 是 int
	std::thread worker1();

	//声明一个线程对象
	std::thread worker2{};

	//创建线程并立即启动DoWork内的操作
	std::thread worker(DoWork);
	worker.join();

	std::cin.get();
}
#endif