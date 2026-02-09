//#include <iostream>
//#include <vector>
//
//#include "String.h"
//
//std::vector<String> ParseShader()
//{
//	//假设vs，fs最终计算值是abc、def
//	//vs,fs先在栈上创建（但String成员m_Buffer是指向堆）
//	String vs = "abc";
//	String fs = "def";
//	std::vector<String> results;
//	//触发了 String 类的拷贝函数 
//	results.push_back(vs);//第一次拷贝
//	results.push_back(fs); //容量不够触发了第二次和第三次拷贝
//	 
//	return  results;
//}
//
//int main()
//{
//	std::vector<String> result = ParseShader();
//
//	std::cout << result[0] << std::endl;
//	std::cout << result[1] << std::endl;
//	std::cin.get();
//} 