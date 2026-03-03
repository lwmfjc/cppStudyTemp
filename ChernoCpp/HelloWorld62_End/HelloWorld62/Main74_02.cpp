#ifdef LY_EP74

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

	//std::shared_ptr和std::make_shared定义在memory中
	std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
	for (int i = 0; i < sharedPtrs.size(); i++)
	{
		sharedPtrs[i] = std::make_shared<Vector2>();
	}

	__debugbreak();

}
#endif