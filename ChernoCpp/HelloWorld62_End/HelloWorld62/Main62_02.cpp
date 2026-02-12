#ifdef LY_EP62_

#include <iostream>
#include <thread>
 
void DoWork()
{

}

int main()
{
	// 这是一个函数声明，声明一个函数名
	// 为 worker，没有参数，返回类型
	// 是 int
	std::thread worker1();

	//创建的是一个“空”线程对象，内部没有关联
	// 任何实际的执行函数，也不启动线程
	std::thread worker2{};

	//创建线程并立即启动DoWork内的操作
	std::thread worker(DoWork);

	//...启动->到join这期间的代码并
	//不会阻塞

	//主线程会等待
	//主线程会停在 join() 这一行，像在车站等
	// 朋友一样，直到子线程这辆车“到站”并合
	// 二为一，主线程才会继续往下走。
	worker.join();

	//子线程完成前不会执行该行代码
	std::cin.get();
}
#endif