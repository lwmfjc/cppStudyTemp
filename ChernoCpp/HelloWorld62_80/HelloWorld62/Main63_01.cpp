#ifdef LY_EP63_

#include <iostream> 
//引入了本节所需要的大部分内容
//跨平台计时
#include <chrono>
//线程相关
#include <thread>

int main()
{
	//为了使用1s表示1秒的用法
	using namespace std::literals::chrono_literals;

	//获取当前时间
	//auto--> std::chrono::steady_clock::time_point
	auto start = std::chrono::high_resolution_clock::now();

	//模拟耗时
	//指定大概睡眠1秒，会有其他开销
	std::this_thread::sleep_for(1s);
	auto end = std::chrono::high_resolution_clock::now();
	//算出实际时长

	//也可以用auto
	std::chrono::duration<float> duration = end - start;
	std::cout << duration.count() << "s" << std::endl;

	std::cin.get();
}
#endif 