#ifdef LY_EP78_

#include <iostream> 
#include <any>
#include <string> 

void* operator new(size_t size)
{
	//std::string("Che");中Che只有4个字符，所以不会在堆上分配；
	// std::any 在堆上分配了一个用于存储管理逻辑的小型辅助结构。（
	//而且分配了三次）
	std::cout << "Allocating " << size << " bytes" << std::endl;
	return malloc(size);
}

int main()
{
	std::any data; 
	//data = 2;
	data = std::string("Che");
	//请给我 data 内部存储的那个字符串的原件地址
	//std::string& string = std::any_cast<std::string&>(data);
	//std::cout << string << std::endl;
	////请根据 data 内部存储的内容，复印一份新的给我
	//std::string string1 = std::any_cast<std::string>(data);
	//std::cout << string1 << std::endl;

	std::cin.get();
	return 0;
}
#endif