#pragma once // 防止头文件被重复包含
#include <iostream>

class String
{
private:
    char* m_Buffer;
    unsigned int m_Size;

public:
    // 默认构造函数
    String() : m_Buffer(nullptr), m_Size(0) {}

    // 构造函数
    String(const char* string);

    // 拷贝构造函数（深拷贝）
    //拷贝构造函数 (String a = b;)：当你在创建一个新的对象，并用已有的对象初始化它时调用。
    String(const String& other);

    // 析构函数
    ~String();

    // 运算符重载
    char& operator[](unsigned int index);

    // 赋值运算符重载 (a = b;)：当两个对象都已经存在（已经构造完毕），你只是想把其中一个的值覆盖给另一个时调用。
    String& operator=(const String& other); 

    // 友元函数：重载 << 运算符
    friend std::ostream& operator<<(std::ostream& stream, const String& string);

    // 测试函数
    unsigned int& mytest() { return m_Size; } // 简单的内联函数可以直接写在类内
};