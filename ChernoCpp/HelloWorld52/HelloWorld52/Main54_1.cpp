#include <iostream>
#include <string>

struct Vector3
{
	float x, y, z;
	Vector3()
		:x(10), y(11), z(12)
	{

	}
};

int main()
{
	{
		//在栈上分配内存
		int value = 5;
		int array[5];
		array[0] = 1;
		array[1] = 2;
		array[2] = 3;
		array[3] = 4;
		array[4] = 5;
		Vector3 vector;

		std::cout << &value << std::endl;
		std::cout << array << std::endl;
		std::cout << &vector << std::endl;
		
	}//作用域结束后，该作用域内栈上分配所有内容都被弹出（内存被释放）
	//在栈上分配内存和释放内存都只是移动栈指针，几乎没有性能损耗

	//new关键字分配堆内存
	int* hvalue = new int;
	*hvalue = 5;
	int* harray = new int[5];
	harray[0] = 1;
	harray[1] = 2;
	harray[2] = 3;
	harray[3] = 4;
	harray[4] = 5;
	//()可以省略
	Vector3* hvector = new Vector3();

	//必须手动释放内存
	delete hvalue;
	delete[] harray;
	delete hvector;

	std::cin.get();
}