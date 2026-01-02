#include <iostream>

int main()
{
	//关闭编译器的安全检查来强制通过下一行代码
	//项目-属性-c++-语言:符合模式-->否,宽松模式。
	// 编译器会允许一些非标准或旧版本 C++ 的写法
	//char* name = "Charno";
	//ASCII码: 43 68 61 72 6E 6F 00
	const char* name = "Charno";
	name = new char[3] {'a', 'b','\0'};
	//name[2] = 'a'; //不允许
	std::cout << name << std::endl;//允许


	std::cin.get();
}