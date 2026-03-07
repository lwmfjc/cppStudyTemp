#ifdef LY_EP69_
#include <iostream>

int main()
{
	int a = 5;
	double value = a;//隐式转换

	double value1 = 5.25;
	int a1 = value1;//隐式转换

	int a2 = (int)value1;//显示转换

	std::cout << "a:" << a << std::endl;//5
	std::cout << "value:" << value << std::endl;//5
	std::cout << "value1:" << value1 << std::endl;//5.25
	std::cout << "a1:" << a1 << std::endl;//5
	std::cout << "a2:" << a2 << std::endl;//5


	std::cin.get();
	//成功的情况只有一种（0），而失败的原因
	//可以有成千上万种（1, 2, 3...）。
	return 0;
}
#endif