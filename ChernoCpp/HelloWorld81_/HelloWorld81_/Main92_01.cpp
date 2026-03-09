#ifdef LY_EP92_
//在堆上分配内存，创建动态数组
//需要一个指向堆分配内存(数据缓冲区)的指针,随着不断
//添加，当元素越来越多会达到临界点，没有足够空间存储新元素时，
//分配一个新的内存块使它有足够空间容纳这个新元素，将内存块中所有元素
//复制到新内存块，然后删除旧内存块

#include <iostream>   
#include <string>
#include "92_vector.h"

template<typename T>
void PrintVector(const Vector<T>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i] << std::endl;
	}

	std::cout << "==================" << std::endl;
}

int main()
{
	Vector<std::string> vector;
	vector.PushBack("Cherno");
	vector.PushBack("C++");
	vector.PushBack("Vector01");
	vector.PushBack("Vector02");
	vector.PushBack("Vector03");
	vector.PushBack("Vector04");
	vector.PushBack("Vector05");
	vector.PushBack("Vector06");
	vector.PushBack("Vector07");

	PrintVector(vector);
	std::cin.get();
	return 0;
}

#endif