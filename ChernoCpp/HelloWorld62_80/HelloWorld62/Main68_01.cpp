#ifdef LY_EP68_
#include <iostream>

class Base
{
public:
	Base() { std::cout << "Base constructor\n"; }
	~Base() { std::cout << "Base destructor\n"; }
};

class Derived : public Base
{
public:
	Derived() { std::cout << "Derived constructor\n"; }
	~Derived() { std::cout << "Derived destructor\n"; }
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