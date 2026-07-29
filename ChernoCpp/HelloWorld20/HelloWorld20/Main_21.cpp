#ifdef LY_EP21
#include <iostream>

//extern：表示这个变量在其他地方（可能是其他源文件）已经定义
extern int s_Variable ;

int main()
{
	std::cout << s_Variable << std::endl;
	std::cin.get();
}

#endif