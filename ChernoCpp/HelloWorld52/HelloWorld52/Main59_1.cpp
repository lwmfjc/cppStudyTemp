#include <iostream>
#include <vector>

void PrintValue(int value)
{
	std::cout << "Value: " << value << std::endl;
}

//func：函数指针
void ForEach(const std::vector<int>& values, void(*func)(int))
{
	for (int value : values)
	{
		func(value);
	}
}

int main()
{
	std::vector<int> values = { 1,4,3,2,5 };
	ForEach(values, PrintValue);
	std::cout << "===" << std::endl;

	//使用lambda表达式，下一集会详细讲解
	//ForEach接收一个函数，该函数只有一个参数
	ForEach(values, [](int value)
		{
			std::cout << value << std::endl;
		}
	);


	std::cin.get();
}