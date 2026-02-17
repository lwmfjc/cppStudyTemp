#ifdef LY_EP65_
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> values = { 3,5,1,4,2 }; 

	//谓词函数询问：a是否应该排在b之前
	std::sort(values.begin(), values.end(), [](int a, int b)
		{ 
			if (a == 1)
			{
				//如果第一个数a是1，那么a不能在前面
				return false;
			}
			if (b == 1)
			{
				//如果第二个数b是1，那么a在前面
				return true;
			}
			//其他情况：如果a<b，那么a排前面
			return a < b;
		});

	for (int value : values)
	{
		std::cout << value << std::endl;
	}

	std::cin.get();
}
#endif