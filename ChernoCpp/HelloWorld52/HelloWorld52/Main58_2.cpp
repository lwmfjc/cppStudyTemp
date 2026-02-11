#include <iostream>  

void HelloWorld()
{
	std::cout << "HelloWorld!" << std::endl;
} 

int main()
{ 
	//使用别名
	typedef void(*HelloWorldFunction)();
	//声明并赋值
	HelloWorldFunction function = HelloWorld;

	function();

	std::cin.get();
}