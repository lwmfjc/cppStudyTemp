//#include <iostream>
//#include <stdlib.h>
//#include <string>
//
//int main()
//{
//	//(const char [7])"Cherno"，7字节，因为末尾有一个空字符'\0'
//	"Cherno";
//	std::cout << "Cher\0no" << std::endl;//Cher
//
//	const char name[8] = "Che\0rno";
//	std::cout << strlen(name) << std::endl;//3,不把\0算在内
//
//	/* 错误的，某些编译器允许编译通过,但没效果
//	char* name1 = "Cherno";
//	name1[2] = 'a';
//	std::cout << name1 << std::endl;//Cherno
//	*/
//
//	//一定要修改的话
//	char name2[] = "Cherno";
//	name2[2] = 'a';
//	std::cout << name2 << std::endl;//Charno
//
//
//
//	std::cin.get();
//}