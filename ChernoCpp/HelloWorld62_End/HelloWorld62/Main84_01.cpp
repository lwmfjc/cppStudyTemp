#ifdef LY_EP84_

#include <iostream>  
#include <memory>

struct AllocationMetrics
{
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;
	
	uint32_t CurrentUsage()
	{
		return TotalAllocated - TotalFreed;
	}
};

static AllocationMetrics s_AllocationMetrics;

//重写operator new 的全局函数，
//链接器会转而链接这个函数
void* operator new(size_t size)
{
	s_AllocationMetrics.TotalAllocated += size;
	std::cout << "Allocating " << size << " bytes\n";
	return malloc(size);
}

//重写特定函数签名来获取特定的释放大小的信息
void operator delete(void* memory, size_t size)
{

	s_AllocationMetrics.TotalFreed += size;
	std::cout << "Freeing " << size << " bytes\n";
	free(memory);
}

struct Object
{
	int x, y, z;
};

/*
内存使用情况
*/
static void PrintMemoryUsage()
{
	std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes.\n";
}


int main()
{
	PrintMemoryUsage();
	Object* obj = new Object;

	//正好12字节，在 C++ 中，类/结构体本身不包含任何运行时开销。
	std::cout << "Size of Object: " << sizeof(Object) << std::endl;

	PrintMemoryUsage();
	std::string s = "Cherno";

	PrintMemoryUsage();
	std::cout << "=========" << std::endl;

	//这行代码仍会分配12字节
	std::unique_ptr<Object> obj1 = std::make_unique<Object>();
	PrintMemoryUsage();
	std::cout << "**********" << std::endl;

	{
		std::unique_ptr<Object> obj =
			std::make_unique<Object>();
		PrintMemoryUsage();
	}

	PrintMemoryUsage();

	std::cin.get();
	return 0;
}

/*
Memory Usage: 0 bytes.
Allocating 12 bytes
Size of Object: 12
Memory Usage: 12 bytes.
Allocating 8 bytes
Memory Usage: 20 bytes.
=========
Allocating 12 bytes
Memory Usage: 32 bytes.
**********
Allocating 12 bytes
Memory Usage: 44 bytes.
Freeing 12 bytes
Memory Usage: 32 bytes.
*/
#endif