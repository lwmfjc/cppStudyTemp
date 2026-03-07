#ifdef LY_EP89_

//c++11才引入了右值引用
#include <iostream>   

class String
{
public:
	String() = default;

	//构造函数
	String(const char* string)
	{
		printf("Created!\n");
		//不包括\0
		m_Size = strlen(string);
		m_Data = new char[m_Size];
		memcpy(m_Data, string, m_Size);
		std::cout << "String(const char* string)" << std::endl;
	}
	
	//复制构造函数
	String(const String& other)
	{
		printf("Copied!\n");
		//不包括\0
		m_Size = other.m_Size;
		m_Data = new char[m_Size];

		//在 C++ 中，访问控制（public/private）是基于“类（Class）”层面的，而不是基于“对象（Object）”层面的。
		//简单来说：只要是在 String 类的成员函数内部，你就可以访问任何 String 对象的私有成员。
		memcpy(m_Data, other.m_Data, m_Size);

		std::cout << "String(const String& other)" << std::endl;
	}
	 

	~String()
	{
		delete[] m_Data;
		printf("Destroyed!\n");
		std::cout << "~String()" << std::endl;
	}

	void Print()
	{
		for (uint32_t i = 0; i < m_Size; i++)
			printf("%c", m_Data[i]);
		printf("\n");
	}
private:
	char* m_Data;

	//这是一个通过 typedef 或 using 定义的类型，表示
	//无符号整型32位数。
	// int 在某些古老的 16 位系统上可能是 2 字节，在现代系统上通常是 4 字节，uint32_t 强制规定在任何符合标准的编译器上，它永远是 32 位（4 字节）
	uint32_t m_Size;
};

class Entity
{
public:
	Entity(const String& name)
		:m_Name(name)
	{
		std::cout << "Entity(const String& name)" << std::endl;
	}  

	void PrintName()
	{
		m_Name.Print();
	}

private:
	String m_Name;
};

int main()
{
	//隐式构造函数构造String对象，调用String(const char* string)构造函数
	//Entity entity("Cherno");

	//临时对象String("Cherno")的生命周期直到支持它的那个“完整表达式”计算完成为止，即该行代码分号结束时
	//!!现在main函数创建这个(临时)对象后，传(复制)给Entity构造函数的当参数使用，又马上销毁了这个临时对象(只留下复制的)
	Entity entity(String("Cherno"));

	entity.PrintName();

	std::cin.get();
	return 0;
}
/*
Created!
String(const char* string)
Copied!
String(const String& other)
Entity(const String& name)
Destroyed!
~String()
Cherno
*/
#endif