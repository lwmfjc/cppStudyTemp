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

	// 移动赋值运算符：将另一个对象，移入当前这个对象自身
	//语义契约（Semantic Contract）。	C++ 的设计哲学是：让自定义类型的行为表现得像内置类型（如 int）一样。标准做法始终是返回非 const 的 *this 引用
	String& operator=(String&& other) noexcept
	{
		printf("Move Assigned!\n");

		// 1. 自赋值检查 (防止自己移动给自己，如 a = std::move(a)，
		// 因为如下是会释放旧资源的，所以移动给自己就什么都没有了)
		if (this != &other)
		{
			// 2. 释放旧资源 (dest[当前对象] 已经有内存了，必须先删掉，否则内存泄漏)
			delete[] m_Data;

			// 3. 窃取资源
			m_Size = other.m_Size;
			m_Data = other.m_Data;

			// 4. 将原对象置空 (让它变成空壳)
			other.m_Data = nullptr;
			other.m_Size = 0;
		}

		//找到 this 指向的对象，返回它的引用（别名），
		// 而不是创建一个新的副本
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
	{
		std::cout << "=====0=====" << std::endl;


		//使用String(const char* string)构造String对象，Created!
		String apple = "Apple";
		//使用默认构造函数构造String对象
		String dest;

		std::cout << "=====1=====" << std::endl;
		std::cout << "Apple: ";
		apple.Print();
		std::cout << "Dest: ";
		dest.Print();
		std::cout << "=====1=====" << std::endl;

		//使用移动赋值运算符将apple的资源移入dest，Move Assigned!
		//相当于dest.operator=(std::move(apple));
		dest = std::move(apple);

		std::cout << "=====2=====" << std::endl;
		std::cout << "Apple: ";
		apple.Print();
		std::cout << "Dest: ";
		dest.Print();
		std::cout << "=====2=====" << std::endl;

		//综上，没有任何复制就移动了整个字符数组的所有权，交换了两个
		//变量
	}
	

	std::cin.get();
	return 0;
}
/* 
=====0=====
Created!
String(const char* string)
=====1=====
Apple: Apple
Dest:
=====1=====
Move Assigned!
=====2=====
Apple:
Dest: Apple
=====2=====
Destroyed!
~String()
Destroyed!
~String()
*/
#endif