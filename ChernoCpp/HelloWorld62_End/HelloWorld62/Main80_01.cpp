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

int main()
{

	//std::string 在栈上预留了 15 字节 的缓冲区，无需堆分配。
	std::string name = "Yan Chernikov";//13个字符 

	//Debug模式下输出Allocating 8 bytes of memory.（调试代理、迭代器调试需要的8字节）
	//Release模式下没有输出
	std::string name1 = "012345678901234567891";//21个字符 

	/*现代 CPU 处理内存时，如果地址是 16 或 32 的倍数，效率最高。以下是输出
	Allocating 32 bytes of memory.
	*/

	std::cin.get();
	return 0;
}
#endif