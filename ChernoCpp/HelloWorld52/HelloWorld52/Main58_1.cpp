#include <iostream>  

void HelloWorld()
{
	std::cout << "HelloWorld!" << std::endl;
}


int test(float a)
{
	std::cout << a << "!" << std::endl;
	return 1;
}

int main()
{
	//function的类型->void (*function)()
	auto function1 = &HelloWorld;
	//&可以省略，因为有隐式转换
	auto function = HelloWorld;
	//相当于
	void(*function2)() = HelloWorld;
	int(*function3)(float) = test;

	function();
	(*function)();
	function1();
	(*function1)();
	function2();
	(*function2)();

	function3(3.0);
	std::cin.get();
}