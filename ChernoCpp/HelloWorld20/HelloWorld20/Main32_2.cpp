//#include <iostream>
//
//int main()
//{
//	const char* name = "Cherno";
//	const char* name_ = u8"Cherno";
//
//	//字符串中的每个字符都是宽字符（wchar_t 类型）,
//	//通常是16位或32位，取决于系统(大小平台相关)
//	//L 前缀表示这是一个宽字符字符串
//	const wchar_t* name2 = L"Cherno";
//
//	// C++11后的UTF-16字符串,固定每个字符2字节
//	const char16_t* name3 = u"Cherno";
//
//	// C++11后的UTF-32字符串,固定每个字符4字节
//	const char32_t* name4 = U"Cherno";
//
//	std::cin.get();
//}