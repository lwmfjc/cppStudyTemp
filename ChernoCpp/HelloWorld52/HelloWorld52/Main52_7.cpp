#include <iostream>
#include <utility> 

#include "String.h"


std::pair<String,String> ParseShader()
{
	//假设vs，fs最终计算值是abc、def 
	String vs = "abc";
	String fs = "def"; 

	//std::make_pair 是一个按值传递（Pass by Value）的函数。
	return  std::make_pair(vs,fs);
}

int main()
{

	std::pair<String, String> result = ParseShader(); 
	std::cout << "======" << std::endl;
	std::cout << std::get<0>(result) << std::endl;
	std::cout << std::get<1>(result) << std::endl;
	std::cout << result.first << std::endl;
	std::cout << result.second << std::endl;
	std::cin.get();
}