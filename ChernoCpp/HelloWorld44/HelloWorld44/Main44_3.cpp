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
		//向堆申请m_Size字节的空间
		m_Buffer = new char[m_Size + 1];

		/*for (int i = 0; i < m_Size; i++)
			m_Buffer[i] = string[i];*/

			//不使用上面的，而是使用简短的函数拷贝
			//工作方式：它从 src 指向的地址开始，连续复制 count 个字节到 dest 指向的地址。
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = '\0';

	}

	
	////如果没有给出复制构造函数，编译器会默认给出这样一个构造函数
	//String(const String& other) 
	//{
	//	//C++ 的权限控制是基于“类”（Class）的，而不是基于“对象”（Instance）。
	////编译器认为：既然你已经身处 String 类的内部代码中，你就是“自己人”。作为一个 String 类，你理所当然知道如何处理另一个 String 类的内部数据。
	//	//std::cout << other.m_Size;
	//}

	//让该函数在类外访问String私有成员
	friend std::ostream& operator<<(std::ostream& stream, const String& string);

	~String()
	{
		delete[] m_Buffer;
	}

	//测试,无意义
	unsigned int& mytest()
	{
		return m_Size;
	}

	/*
	返回引用意味着你拿到了内存中那个字符的“本体”，而不是它的副本。这样你不仅可以读它（char c = string[2]），还可以写它（string[2] = 'a'）
	*/
	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}
};

//如果是成员函数，调用方式会变成 string << std::cout;（这看起来非常反人类）。
//为了实现 std::cout << string; 这种标准写法，左边的对象必须是 std::ostream。
// 因为我们没法修改 C++ 标准库的 ostream 类，所以只能在自己的类里写一个全局函数
// ，并把它设为“友元”。
std::ostream& operator<<(std::ostream& stream, const String& string)
{
	//只有将该函数(operator<<定义为友元函数，才能在类外访问String私有成员
	//std::cout 在处理 char* 时，它的内部逻辑大致如下：
	//它拿到的只是一个内存地址。
	//它并不知道你这个字符串到底有多长（它不读你的 m_Size 变量）。
	//它的唯一指令是：“从这个地址开始打印，直到看到 \0（空终止符）为止。”
	stream << string.m_Buffer;
	return stream;
}

int main()
{
	String string = "cherno";
	std::cout << string << std::endl;

	String second = string;
	std::cout << second << std::endl;

	second[2] = 'a';

	//测试,无意义
	//编译器眼中看到的不是一个函数调用，而是一个左值（lvalue），
	// 也就是一个可以直接被赋值的内存位置。这行代码等同于直接操作：
	// second.m_Size = 3;
	second.mytest() = 3;
	std::cout << second.mytest() << std::endl;//3


	std::cout << string << std::endl;//charno
	std::cout << second << std::endl;//charno


	std::cin.get();
}