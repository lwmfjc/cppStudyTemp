#ifdef LY_EP90_

//c++11才引入了右值引用
#include <iostream>   
#include <utility> // std::move 在这个头文件里

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


	//移动构造函数
	//接收一个右值引用参数，表示可以从一个将要被销毁的临时对象中“窃取”资源，而不是复制资源。
	//如果手动定义了“移动构造函数”，编译器就不再为你自动生成“默认赋值运算符”了。
	String(String&& other) noexcept
	{
		printf("Moved!\n");
		//不包括\0
		m_Size = other.m_Size;
		m_Data = other.m_Data;

		other.m_Size = 0;//将原对象的大小置为0，表示它不再拥有资源

		//把被接管控制权的资源指针置空，防止原对象的析构函数删除已经被移动的资源
		other.m_Data = nullptr;


		std::cout << "String(String&& other)" << std::endl;
	}

	~String()
	{
		delete[] m_Data;
		printf("Destroyed!\n");
		std::cout << "~String()" << std::endl;
	}

	// 移动赋值运算符
	String& operator=(String&& other) noexcept
	{
		printf("Move Assigned!\n");

		// 1. 自赋值检查 (防止自己移动给自己，如 a = std::move(a))
		if (this != &other)
		{
			// 2. 释放旧资源 (dest 已经有内存了，必须先删掉，否则内存泄漏)
			delete[] m_Data;

			// 3. 窃取资源
			m_Size = other.m_Size;
			m_Data = other.m_Data;

			// 4. 将原对象置空 (让它变成空壳)
			other.m_Data = nullptr;
			other.m_Size = 0;
		}

		return *this;
	}

	//拷贝赋值运算符
	String& operator=(const String& other)
	{
		printf("Copy Assigned!\n");
		if (this != &other)
		{
			delete[] m_Data;
			m_Size = other.m_Size;
			m_Data = new char[m_Size]; // 必须申请新内存
			memcpy(m_Data, other.m_Data, m_Size);
		}
		return *this;
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



	//Entity(String&& name)
	//	//一旦右值引用有了名字，它在后续表达式中就变成了左值。
	//	//编译器会想：“这个 name 虽然是引用进来的，但它现在是有名有姓的变量，为了安全起见，我必须调用 复制构造函数 来保护它。
	//	:m_Name(name)
	//{
	//	std::cout << "Entity( String&& name)" << std::endl;
	//}



	//接收一个临时对象作为参数，使用移动语义来构造 Entity 对象，避免不必要的复制，提高性能。
	Entity(String&& name)
		//强转为右值引用，告诉编译器：我知道 name 是一个左值，但我想把它当作一个将要被销毁的临时对象来处理，所以请调用 移动构造函数 来构造 m_Name。
		//:m_Name((String&&)name) //这种写法也行
		:m_Name(std::move(name))  // 将左值 name 强行转回右值
	{
		std::cout << "Entity( String&& name)" << std::endl;
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
	//这里将"Cherno"隐式调用构造函数构造了一个String
	//之后move给了Entity（Entity内部的m_Name接管了这个临时String指针指向的堆内存）
	Entity entity("Cherno");
	entity.PrintName();
	std::cout << "===0==" << std::endl;
	String string = "Hello";
	std::cout << "===1==" << std::endl;
	String dest = string;//这是复制
	std::cout << "===2==" << std::endl;
	String dest1 = std::move(string);//调用移动构造函数
	dest1.Print();
	std::cout << "===3==" << std::endl;
	//如果没写移动赋值,编译器会“退而求其次”，去调用拷贝赋值运算符 operator=(const String & other)
	dest = "abc";
	std::cout << "===4==" << std::endl;
	 
	dest = std::move(string);
	dest.Print();//string已经被移动了，变成了空壳，所以dest打印出来是空的

	std::cin.get();
	return 0;
}
/*
Created!
String(const char* string)
Moved!
String(String&& other)
Entity( String&& name)
Destroyed!
~String()
Cherno
===0==
Created!
String(const char* string)
===1==
Copied!
String(const String& other)
===2==
Moved!
String(String&& other)
Hello
===3==
Created!
String(const char* string)
Move Assigned!
Destroyed!
~String()
===4==
Move Assigned!

*/
#endif