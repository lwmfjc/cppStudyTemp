//#include <iostream>
//#include "String.h"
//
//String* ParseShader()
//{
//	//假设vs，fs最终计算值是abc、def
//	//vs,fs先在栈上创建（但String成员m_Buffer是指向堆）
//	String vs = "abc";
//	String fs = "def";
//
//	//这种语法在c++20才能编译通过
//	return new String[]{ vs,fs };
//} 
//
//int main()
//{ 
//	String* result =ParseShader();
//
//	std::cout << result[0] << std::endl;
//	std::cout << result[1] << std::endl;
//	std::cin.get();
//}
///*
//Assignment Operator Called!abc
//Assignment Operator Called!def
//abc
//def
//*/