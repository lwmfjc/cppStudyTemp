#ifdef LY_EP32_3

//#include <iostream>
//#include <string>
//
//#include <stdlib.h>
//
//int main()
//{
//	//启用了 "text"s 语法，让创建 std::string 对象更加
//	// 直观、类型安全，特别是在自动类型推导和复杂字符串场景下非常有用。
//	using namespace std::string_literals;
//	//报错
//	//std::string name0 = "Cherno" + " hello";
//	std::string name0 = std::string("Cherno") + " hello";
//
//	//// 普通运算符重载：没有引号
//	//std::string operator+(const std::string & a, const std::string & b);
//	// 字面量运算符：必须有 "" 
//	//std::string operator""s(const char* str, size_t len);
//
//	//std::string operator""s(const char* str, size_t len);
//	//下面的语句,相当于std::string name1 = operator""s("Cherno", 6) + " hello";
//	std::string name1 = "Cherno"s + " hello";
//	std::cout << name1 << std::endl;
//
//	std::string name2 = u8"Cherno"s + " hello";
//	std::wstring name3 = L"Cherno"s + L" hello";
//	std::u32string name4 = U"Cherno"s + U" hello";
//	//R 表示 Raw string literal（原始字符串字面量），括号内的内容会完全按照原样被存储，包括换行符、制表符等特殊字符。
//	const char* example = R"(Line1
//Line2
//Line3
//Line4)";
//	/*
//Line1
//Line2
//Line3
//Line4
//	*/
//	std::cout << example << std::endl;
//	const char* example1 = "Line1\n"
//		"Line2\n"
//		"Line3\n"
//		"Line4";
//	std::cout << example1 << std::endl;
//	std::cin.get();
//}



#endif