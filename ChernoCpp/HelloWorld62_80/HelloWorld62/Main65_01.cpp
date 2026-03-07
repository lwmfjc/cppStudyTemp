#ifdef LY_EP65_
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> values = { 3,5,1,4,2 };
	//默认是升序排序
	//std::sort(values.begin(), values.end());

	//提供函数，这里是较大值排前面
	//第三个参数：对数组中两个数据调用这个函数后返回 true 
	//代表询问第一个元素应该排在第二个元素之前（吗？这里是肯定），
	//不做处理。返回false 则表示不应该，得交换他们
	//std::sort(values.begin(), values.end(),		std::greater<int>());

	//谓词函数询问：a是否应该排在b之前
	std::sort(values.begin(), values.end(), [](int a, int b)
		{
			//先判断什么情况下是true：b<a时
			//返回true时，a排在b之前
			//推断：b<a时，即a>b时，a排在b之前，所以这里是降序
			//return b < a;

			//a<b的情况下，a在b之前，即升序
			return a < b;
		});

	for (int value : values)
	{
		std::cout << value << std::endl;
	}

	std::cin.get();
}
#endif