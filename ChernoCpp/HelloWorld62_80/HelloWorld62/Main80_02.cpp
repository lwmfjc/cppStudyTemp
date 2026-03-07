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

int main()
{
	//std::string 在栈上预留了 15 字节 的缓冲区，无需堆分配。
	//用于 SSO 的本地数组大小定义为 16 字节（包括结尾的 null 字符），因此可以存储最多 15 个字符的字符串。
	std::string name = "Yan Chernikov";//13个字符 

	std::string name1 = "012345678901234567891";//21个字符 

	//substr(起始位置，长度)
	//正好15，没有堆分配
	std::string firstName1 = name1.substr(0, 15);
	std::cout << "firstName1--length:" << firstName1.size() << std::endl; 
	//小于15，没有堆分配
	std::string lastName1 = name1.substr(10, 20);
	//没有赋值，但是产生了临时对象，进行了堆分配 
	name1.substr(0, 20);
	 

	std::cout << "=======0========" << std::endl;

	//堆分配64字节
	std::string name2 = "01234567890123456789012345678901234567890123456789";//50个字符 

	std::cout << "=======1========" << std::endl;
	//堆分配48字节（因为substr的结果加上\0是33字节）
	std::string firstName2 = name2.substr(0, 32);
	std::cout << "=======2========" << std::endl;
	//堆分配32字节
	std::string lastName2 = name2.substr(0, 31);


	//PrintName(name);

	std::cin.get();
	return 0;
}
/*
Allocating 32 bytes of memory.
firstName1--length:15
Allocating 32 bytes of memory.
=======0========
Allocating 64 bytes of memory.
=======1========
Allocating 48 bytes of memory.
=======2========
Allocating 32 bytes of memory.
*/
#endif