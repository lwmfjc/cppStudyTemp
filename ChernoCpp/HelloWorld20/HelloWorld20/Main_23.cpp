#ifdef LY_EP23_
#include <iostream>

//默认情况下是无符号整型unsigned int
enum Example:unsigned char
{
	//如果不指定的话，第一个
	//为0，然后逐个增加
	//只要没有指定的值，都会根据前一个指定的值逐个增加
	A,B,C
};

enum e_MyLong : long
{
	//如果不指定的话，第一个
	//为0，然后逐个增加
	//只要没有指定的值，都会根据前一个指定的值逐个增加
	A1, B1, C1
};


int a = 0;
int b = 1;
int c = 2;


int main()
{
	Example value = B;//如果e_MyLong里面也有B的话，编译器会报错
	Example value1 = Example::B;

	//if (value == 1) //也可以这么写
	if (value == B) {
		std::cout << "get" << std::endl;
	}
	std::cin.get();
}

#endif