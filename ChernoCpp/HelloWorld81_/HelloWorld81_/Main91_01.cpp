#ifdef LY_EP91_

#include <iostream>   
#include <array>

int main()
{
	int k = 3;
	const int const_k = 5; //常量表达式，编译时可确定

	//栈分配
	//int myarray[k];//编译出错
	//const_k必须是编译时已知的常量
	int myarray[const_k];
	for(int i=0;i<const_k;i++)
	{ 
		//未初始化，值为栈上的垃圾值
		std::cout << myarray[i] << std::endl;
	}
	//myarray在栈帧弹出时自动释放


	//堆分配，且用指针寻址
	//动态分配，大小无需在编译时确定
	int* heapArray = new int[k];

	delete[] heapArray; //释放堆内存

	//c++11提供的标准数组，大小必须在编译时确定
	//这是个模板类，通过模板指定类型和大小
	// _EXPORT_STD template <class _Ty, size_t _Size>
	std::array<int, 5> collection;

	collection.size();//成员函数，返回数组大小

	for (int i = 0; i < collection.size(); i++)
	{
		std::cout << collection[i] << std::endl;
	}

	//要让 for (int i : collection) 运行，C++ 编译器会寻找两个特定的函数：begin() 和 end()。
	for (int i : collection)
	{

	}

	std::cin.get();
	return 0;
} 
#endif