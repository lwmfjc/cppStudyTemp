#include "String.h"
#include <cstring> // 必须包含 cstring 才能使用 strlen 和 memcpy

// 构造函数
String::String(const char* string)
{
	m_Size = strlen(string);
	m_Buffer = new char[m_Size + 1];
	memcpy(m_Buffer, string, m_Size);
	m_Buffer[m_Size] = '\0';
}

// 拷贝构造函数
String::String(const String& other)
	: m_Size(other.m_Size)
{
	std::cout << "Copied String!" << other << std::endl;
	m_Buffer = new char[m_Size + 1];
	memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
}

//赋值运算符 
String& String::operator=(const String& other)
{
	std::cout << "Assignment Operator Called!" << other << std::endl;

	// 1. 自赋值检查 (防止 s1 = s1 的骚操作)
	if (this == &other)
		return *this;

	// 2. 释放当前对象旧的内存，防止内存泄漏
	delete[] m_Buffer;

	// 3. 申请新空间并拷贝内容
	m_Size = other.m_Size;
	m_Buffer = new char[m_Size + 1];
	memcpy(m_Buffer, other.m_Buffer, m_Size + 1);

	// 4. 返回对象自身，支持链式赋值 (a = b = c)
	return *this;
}

// 析构函数
String::~String()
{
	delete[] m_Buffer;
}

// 下标运算符重载
char& String::operator[](unsigned int index)
{
	return m_Buffer[index];
}

// 友元函数定义（注意：定义时不需要加 String::，也不需要加 friend 关键字）
std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}