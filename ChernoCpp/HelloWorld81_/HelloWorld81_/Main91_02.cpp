#ifdef LY_EP91_

#include <iostream>   

//size_t 的使命是“能够表示内存中最大的对象”，
//在几位的机器上运行就是几位大小
template<typename T, size_t S>
class Array
{
public:

	//编译期常量
	constexpr size_t Size() const
	{
		return S;
	}

	//这样会导致取出数组元素后会被复制，且也无法修改
	//T operator[] (int index)

	//返回引用，是能修改的左值
	//1. 普通版本：允许读写
	T& operator[] (size_t index)
	{
		return m_Data[index];
	}


	//2：只允许读,而且返回const引用
	//通过这个返回的普通引用，别人依然可以修改 m_Data 里的内容，这违背了函数末尾 const 的初衷
	 //T& operator[] (int index) const

	//2：只允许读,而且返回const引用
	//取决于你调用该函数的对象本身是否是 const,是const
	//对象则调用该重载版本
	const T& operator[] (size_t index) const
	{
		return m_Data[index];
	}

	T* Data()
	{
		return m_Data;
	}

	//常量版本
	const T* Data() const
	{
		return m_Data;
	}

private:
	T m_Data[S];
};

int main()
{
	//每次创建新类，编译器都会根据模板参数生成一个新的类
	Array<int, 5> data;


	//每个字节都是 1
	memset(&data, 1, data.Size() * sizeof(int));

	//每个字节都是 2
	memset(data.Data(), 2, data.Size() * sizeof(int));

	//把数组中每个字节设为0
	memset(&data[0], 0, data.Size() * sizeof(int));

	//编译期的断言检查。让编译器在把代码编译成程序之前，先检查一下你的逻辑对不对，如果条件不满足，编译器会直接报错并拒绝生成程序 
	static_assert(data.Size() < 10, "Size is too large!");

	//因为data.Size()是编译期常量
	Array<std::string, data.Size()> a;

	//
	const auto& arrayReference = data;

	//arrayReference[2] = 3; //

	//arrayReference是const修饰的，编译器只能调用带有 const 后缀的版本
	std::cout << arrayReference[2] << std::endl;

	for (size_t i = 0; i < data.Size(); i++)
	{
		//data[i] = i;
		std::cout << data[i] << std::endl;
	}

	Array<std::string, 3> data1;
	data1[0] = "hello";
	data1[1] = "world";
	for (size_t i = 0; i < data1.Size(); i++)
	{
		//data[i] = i;
		std::cout << data1[i] << std::endl;
	}

	std::cin.get();
	return 0;
}
/*
0
0
0
0
0
0
hello
world

*/
#endif