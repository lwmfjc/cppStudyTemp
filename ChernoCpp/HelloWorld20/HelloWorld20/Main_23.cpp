#ifdef LY_EP23
#include <iostream>

//默认情况下是无符号整型unsigned int
enum Example:unsigned char
{
	//如果不指定的话，第一个
	//为0，然后逐个增加
	//只要没有指定的值，都会根据前一个指定的值逐个增加
	A,B,C
};


int a = 0;
int b = 1;
int c = 2;


//int main()
//{
//	Example value = B;
//
//	//if (value == 1) {
//	if (value == B) {
//		std::cout << "get" << std::endl;
//	}
//	std::cin.get();
//}

#endif