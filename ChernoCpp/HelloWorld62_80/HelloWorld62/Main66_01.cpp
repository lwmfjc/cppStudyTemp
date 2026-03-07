#ifdef LY_EP66_
#include <iostream>

int main()
{ 
	//小端法，低字节的数据存储在内存的低地址处，
	// 高字节的数据存储在内存的高地址处
	//Ox00000032
	int a = 50;// 32 00 00 00 
	 
	//隐式转换，a隐式转换成了double类型
	//相当于 double value =(double)a
	//Ox404900000000000000，double数值50
	//的16进制表示为0x4049000000000000
	double value = a;// 00 00 00 00 00 00 49 40 
	std::cout << value << std::endl;

	std::cin.get();
}
#endif