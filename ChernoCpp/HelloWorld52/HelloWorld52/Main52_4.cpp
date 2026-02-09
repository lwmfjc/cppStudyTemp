//#include <iostream>
//#include <array>
//
//#include "String.h"
//
//std::array<String,2> ParseShader()
//{
//	//假设vs，fs最终计算值是abc、def
//	//vs,fs先在栈上创建（但String成员m_Buffer是指向堆）
//	String vs = "abc";
//	String fs = "def";
//	std::array<String, 2> results;
//	//触发了 String 类的拷贝赋值运算符（Assignment Operator）
//	//此时 results[0] 内部的 m_Buffer 会申请一块新堆内存，并将 vs 指向的内容复制过来。现在内存中有两份 "abc"。
//	results[0] = vs;
//	results[1] = fs; 
//
//	//由于现代编译器的 RVO（返回值优化），results 数组通常不会被拷贝，而是直接在 main 函数的 result 变量位置“原地出生”。且result指向的是上面申请的新堆内存
//	return  results;
//}
//
//int main()
//{
//	std::array<String, 2> result = ParseShader();
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