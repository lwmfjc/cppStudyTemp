#ifdef LY_EP68_
#include <iostream>

class Base
{
public:
	Base() { std::cout << "Base constructor\n"; }
	
	//析构函数加virtual，表示这个类可能被拓展（继承），可能会有一个析构函数
	//需要被调用
	virtual ~Base()  { std::cout << "Base destructor\n"; }
};

class Derived : public Base
{
public:
	Derived() { m_array = new int[5];  std::cout << "Derived constructor\n"; }
	~Derived() { delete[] m_array; std::cout << "Derived destructor\n"; }
private:
	int* m_array;
};

int main()
{
	Base* base = new Base();
	delete base;
	std::cout << "------------------\n";
	Derived* derived = new Derived();
	delete derived;
	std::cout << "------------------\n";
	Base* poly = new Derived();
	delete poly;

	std::cin.get();
}
#endif