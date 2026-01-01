#include <iostream> 
class Entity
{ 
	constexpr int size = 5;
	int arr[size];
};
int main()
{ 

	int a[5];
	std::cout << sizeof(a) << std::endl;//20，数组大小(字节数)
	std::cout << sizeof(a)/sizeof(int) << std::endl;//5，数组个数

	int* example = new int[5];
	std::cout << sizeof(example) << std::endl;//8，指针的大小(8字节)
	


	std::cin.get();
}