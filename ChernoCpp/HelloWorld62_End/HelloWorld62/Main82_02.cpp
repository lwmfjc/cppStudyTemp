#ifdef LY_EP82_

#include <iostream>  


class Random
{
public:
	Random(const Random&) = delete;//禁止拷贝
	static Random& Get()
	{
		return s_Instance;
	}
	static float Float()
	{
		return Get().IFloat();
	}
private:

	float IFloat() {
		return m_RandomGenerator;
	}

	float m_RandomGenerator = 0.5f;
	Random() {}

	static Random s_Instance;
};


//定义 
//1. 在全局/静态内存区分配 sizeof(Singleton) 字节的空间。
//2. 在程序启动时，自动调用 Singleton 的构造函数来初始化这块空间。
//由于你使用了作用域解析符 Singleton::，编译器认为这行代码依然属于 Singleton 类的范畴
Random Random::s_Instance;

int main()
{ 
	//先内联Float变成Random::Get().IFloat();
	//之后内联Get和IFloat变 Random::s_Instance.m_RandomGenerator
	//最后这里还进行常量折叠 float number = 0.5f;
	float number = Random::Float();

	std::cout << number << std::endl;

	std::cin.get();
	return 0;
}
#endif