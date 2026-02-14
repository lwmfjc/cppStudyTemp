#ifdef LY_EP63_

#include <iostream> 
//引入了本节所需要的大部分内容
//跨平台计时
#include <chrono>
//线程相关
#include <thread>

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;


	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;//可以省略不存储结束值

		//1000.0f不是重载，而是编译器硬编码的，1000f会编译报错
		float ms = duration.count() * 1000.0f;
		//24ms
		//std::cout << "Timer took " << ms << "ms" << std:: endl;
		//21ms
		std::cout << "Timer took " << ms << "ms\n";// << std::endl;
	}
};

void Function()
{
	//作用域(函数)内创建Timer对象,整个(函数)作用域(结束后)都会被计时
	Timer timer;
	for (int i = 0; i < 100; i++)
		std::cout << "Hello" << std::endl;
}

int main()
{ 
	Function();
	std::cin.get();
}
#endif 