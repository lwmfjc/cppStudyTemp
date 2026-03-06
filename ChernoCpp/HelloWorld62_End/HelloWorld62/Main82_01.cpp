#ifdef LY_EP82_

#include <iostream>  


class Singleton
{
public:
	Singleton(const Singleton&) = delete;//禁止拷贝
	static Singleton& Get()
	{
		return s_Instance;
	}
	void Function() {
		std::cout << "Function" << std::endl;
	}
private:
	float m_Member = 3.4f;
	Singleton() {}

	static Singleton s_Instance;
};


//定义 
//1. 在全局/静态内存区分配 sizeof(Singleton) 字节的空间。
//2. 在程序启动时，自动调用 Singleton 的构造函数来初始化这块空间。
//由于你使用了作用域解析符 Singleton::，编译器认为这行代码依然属于 Singleton 类的范畴
Singleton Singleton::s_Instance;

int main()
{
	//这种写法，调用了Singleton类的复制构造函数，
	//拷贝了所有成员，并创建了一个新的实例（违背单例本意）
	//类定义中Singleton(const Singleton&) = delete;//禁止拷贝
	//Singleton instance = Singleton::Get();

	auto& instantce = Singleton::Get();
	Singleton::Get().Function();

	std::cin.get();
	return 0;
}
#endif