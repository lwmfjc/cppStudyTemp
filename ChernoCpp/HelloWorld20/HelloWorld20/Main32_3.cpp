#include <iostream>
#include <string>

#include <stdlib.h>

int main()
{
	//启用了 "text"s 语法，让创建 std::string 对象更加
	// 直观、类型安全，特别是在自动类型推导和复杂字符串场景下非常有用。
	using namespace std::string_literals; 
	//报错
	//std::string name0 = "Cherno" + " hello";
	std::string name0 = std::string("Cherno") + " hello";

	//std::string operator""s(const char* str, size_t len);
	//下面的语句,相当于std::string name1 = operator""s("Cherno", 6) + " hello";
	std::string name1 = "Cherno"s + " hello";
	std::cout << name1 << std::endl;

	std::cin.get();
}