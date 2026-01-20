#include <iostream>
#include <string>

//写一个最原始的String类
class String
{

private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	//接收一个常量字符，初始化
	String(const char* string)
	{
		//strlen 函数的作用是计算字符串的长度，它会从你提供的指针
		// 地址开始扫描，直到遇到第一个空字符（终止符）\0 为止，
		// 但计数结果不计入这个\0
		m_Size = strlen(string);

	}
};

int main()
{

	std::cin.get();
}