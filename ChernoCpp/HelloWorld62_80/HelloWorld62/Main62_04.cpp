#ifdef LY_EP62_

#include <iostream>
#include <thread>

// 显式包含时间库
//cherno视频里没有却能运行，可能是有些编译器中，
// <thread> 头文件为了实现 sleep_for 等功能，
// 其内部已经写了 #include <chrono>。(ai回答)
#include <chrono> 

static bool s_Finished = false;

void DoWork()
{ 
	using namespace std::literals::chrono_literals;

	std::cout << "Started thread id=" << std::this_thread::get_id() << std::endl;

	while (!s_Finished)
	{
		std::cout << "working..." << std::endl;
		//用std::this_thread给当前线程发命令
		std::this_thread::sleep_for(1s);
	}
}

int main()
{
	std::thread worker(DoWork);

	//主线程自己阻塞自己了
	std::cin.get();
	//用户按下回车后
	s_Finished=true;

	//按下回车后，子线程或许刚进入
	//while语句块{ ，且还没到达打印语句
	//所以可能子线程要再打印一行，之后下
	//一次循环才不会进入


	worker.join();
	std::cout << "===child thread finished~~==" << std::endl;

	//子线程完成前不会执行该行代码
	std::cin.get();
}
#endif
/* 输出
Started thread id=360
working...
working...
working...
working...
working...
working...
		 //这就是用户按下的回车行
working...
===child thread over~==

*/