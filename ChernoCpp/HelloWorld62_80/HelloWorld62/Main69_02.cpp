#ifdef LY_EP69_
#include <iostream>

class Base
{
public:
	Base() {}

	//这里应该把析构函数设为vitual，我只是为了演示
	//只要有虚函数就能用动态转换转换成功，而这个虚函数
	//不一定非得是析构函数
	~Base() {} 

	virtual void test() {}
};

//public Base中 <public> 决定：基类（Base）中的成员在
//派生类（Derived）中保持什么样的访问权限。（public则成员
//的最高权限是public）
class Derived : public Base
{
public:
	Derived() {}
	~Derived() {}
};

class AnotherClass : public Base
{
public:
	AnotherClass() {}
	~AnotherClass() {}
};

int main()
{
	//C风格转换
	double value = 5.25;
	double a1 = value + 5.3;//10.55
	double a2 = (int)value + 5.3;//强制截断，10.3 
	double a3 = (int)(value + 5.3);//强制截断，10 
	std::cout << a1 << std::endl;
	std::cout << a2 << std::endl;
	std::cout << a3 << std::endl;

	// C++风格转换（以下C风格转换都能做到，但是C++风格还会做点
	// 额外的事情）
	double s = static_cast<int>(value) + 5.3;//1 静态转换，会有编译时检查

	//double s1 = static_cast<AnotherClass>(value) + 5.3;//编译失败,没有哪个构造函数支持，即没有 AnotherClass(int)这样的构造函数先隐式转换成AnotherClass

	//AnotherClass s11 = static_cast<AnotherClass*>(value) ;//编译失败，无效的类型转换
	//AnotherClass s12 = static_cast<AnotherClass*>(&value) ;;//编译失败，无效的类型转换


	//2 重新解释转换 //类似类型双关
	AnotherClass* a = reinterpret_cast<AnotherClass*>(&value);//“重新解释转换”，编译通过，即指向该值的指针，解释成：指向另一个类实例的指针


	//3 动态类型转换 //多态时用到
	Derived* derived = new Derived();
	Base* base = derived;
	//检查基类指针是否是(某个)派生类实例 
	//静态转换，但很明显这会出问题(base是指向Derived实例而非AnotherClass)
	AnotherClass* ac1 = static_cast<AnotherClass*>(base);
	AnotherClass* ac1_1 = (AnotherClass*)(base);

	Derived* ac3 = dynamic_cast<Derived*>(base);//编译通过

	AnotherClass* ac2 = dynamic_cast<AnotherClass*>(base);//编译通过，但是返回null
	if (ac3)
	{
		std::cout << "ac3转换成功" << std::endl;//ac3转换成功
	}
	if (ac2)
	{
		std::cout << "ac2转换成功" << std::endl;//没成功
	}

	//4 常量解释转换：移除或添加常量
	//视频没说到

	std::cin.get();
	//成功的情况只有一种（0），而失败的原因
	//可以有成千上万种（1, 2, 3...）。
	return 0;
}
#endif