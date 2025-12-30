#include <iostream>

struct Entity
{
	static int x, y;
	static int x, y;
	static void Print()
	{
		//静态方法无法访问非静态成员变量，因为他
		//不知道访问的是哪个实例的成员变量
		//否则提示C++ a nonstatic member reference must be relative to a specific object
		std::cout << x << "," << y << std::endl;
	}
};

int Entity::x;
int Entity::y;

int main()
{
	Entity::x = 2;
	Entity::y = 3;

	Entity::x = 5;
	Entity::y = 8;

	Entity::Print();
	Entity::Print();
	/*
	5,8
	5,8
	*/

	std::cin.get();
}