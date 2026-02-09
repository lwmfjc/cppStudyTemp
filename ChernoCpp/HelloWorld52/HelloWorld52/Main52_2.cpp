//#include <iostream>
//#include "String.h"
//
//void ParseShader(String* vertexSource, String* fragmentSource)
//{
//	//假设vs，fs最终计算值是abc、def
//	String vs = "abc";
//	String fs = "def";
//
//	//这两行代码执行的是 字符串赋值(内部会拷贝)
//	if (vertexSource) {
//		*vertexSource = vs;
//	}
//	if (fragmentSource) {
//		*fragmentSource = fs;
//	} 
//}
//
//int main()
//{
//	String vs, fs;
//	ParseShader(&vs, &fs);
//	//这种方式允许空指针
//	//ParseShader(nullptr, &fs);
//	std::cout << vs << std::endl;
//	std::cout << fs << std::endl;
//	std::cin.get();
//}
///*
//Assignment Operator Called!abc
//Assignment Operator Called!def
//abc
//def
//*/