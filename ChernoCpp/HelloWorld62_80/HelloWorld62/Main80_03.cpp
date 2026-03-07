#ifdef LY_EP80_

#include <iostream>  
#include <string>

static uint32_t s_AllocaCount = 0;

//重载new运算符
void* operator new(std::size_t size)
{
	s_AllocaCount++;
	printf("Allocating %zu bytes of memory.\n", size);
	return malloc(size);
}

void PrintName(const std::string& name)
{
	std::cout << "Name: " << name << std::endl;
}
void PrintName1(std::string_view name)
{
	std::cout << "Name: " << name << std::endl;
}

int main()
{ 
	//堆分配64字节
	std::string name2 = "01234567890123456789012345678901234567890123456789";//50个字符 

	std::cout << "=======1========" << std::endl;
	//堆分配48字节（因为substr的结果加上\0是33字节）
	std::string firstName2 = name2.substr(0, 32);
	std::cout << "=======2========" << std::endl;
	//堆分配32字节
	std::string lastName2 = name2.substr(0, 31); 

	std::cout << "Allocat times:" << s_AllocaCount << std::endl;//3
	
	//没有产生堆分配，string_view只是一个轻量级的视图，不会复制字符串数据
	//当你对它进行 substr 截取时，它不会修改原始内存，也不会在截取的地方放一个 \0 
	std::string_view firstName3(name2.c_str(), 32);
	//没有产生堆分配
	std::string_view lastName3(name2.c_str(), 31);

	std::cout << "Allocat times:" << s_AllocaCount << std::endl;//3

	//没有产生堆分配
	const char* myStr= "01234567890123456789012345678901234567890123456789";
	

	//没有产生堆分配
	std::string_view lastName4(myStr, 31);

	//没有堆分配
	PrintName("hello");

	//一次堆分配64字节
	PrintName("01234567890123456789012345678901234567890123456789");//40个字符

	//没有堆分配，string_view只是一个轻量级的视图，不会复制字符串数据
	PrintName1("01234567890123456789012345678901234567890123456789");//40个字符



	std::cin.get();
	return 0;
}
/*
Allocating 64 bytes of memory.
=======1========
Allocating 48 bytes of memory.
=======2========
Allocating 32 bytes of memory.
Allocat times:3
Allocat times:3
Name: hello
Allocating 64 bytes of memory.
Name: 01234567890123456789012345678901234567890123456789
Name: 01234567890123456789012345678901234567890123456789
*/
#endif