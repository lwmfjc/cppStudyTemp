#ifdef LY_EP74_

#include <iostream>   
#include <chrono>
#include <vector>
#include <memory>
#include <array>

class Timer
{
public:
	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		//算出起始时间的微秒数 
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		//算出结束时间的微秒数
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		//算出持续时间
		auto duration = end - start;
		//将持续时间转换为毫秒并输出
		double ms = duration * 0.001;
		std::cout << duration << "us (" << ms << "ms)" << std::endl;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};

int main()
{
	struct Vector2
	{
		float x, y;
	};

	{
		std::cout << "Make Shared:" << std::endl;
		//std::shared_ptr和std::make_shared定义在memory中
		//在栈（Stack）上分配的固定大小的数组，存储1000 个 std::shared_ptr 指针对象
		std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
		Timer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
		{
			//make_shared,代码中最耗时的部分 
			sharedPtrs[i] = std::make_shared<Vector2>();
		}

	}
	


	{
		std::cout << "New Shared:" << std::endl;
		//使用new，而且使用shared_ptr来管理内存，shared_ptr是共享式智能指针，可以被多个指针共享
		std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
		Timer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
		{

			sharedPtrs[i] = std::shared_ptr<Vector2>(new Vector2());
		}

	}

	{
		std::cout << "New Unique:" << std::endl;
		//使用unique_ptr来管理内存，unique_ptr是独占式智能指针，不能被复制，但可以被移动
		std::array<std::unique_ptr<Vector2>, 1000> sharedPtrs;
		Timer timer;
		for (int i = 0; i < sharedPtrs.size(); i++)
		{
			 
			sharedPtrs[i] = std::unique_ptr<Vector2>();
		}

	}
	__debugbreak();

}
#endif

/* Release（Debug做了一堆额外的安全操作，更加耗时）
Make Shared:
203us (0.203ms)
New Shared:
343us (0.343ms)
New Unique:
3us (0.003ms)*/