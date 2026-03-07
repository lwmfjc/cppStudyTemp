#ifdef LY_EP78

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

struct CustomClass
{
	std::string s0,s1;
};
int main()
{
	std::any data; 
	data = CustomClass(); 

	std::cin.get();
	return 0;
}
/*
Allocating 8 bytes
Allocating 8 bytes
Allocating 56 bytes
Allocating 8 bytes
Allocating 8 bytes
*/
#endif