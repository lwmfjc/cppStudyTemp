#include <iostream>

class Entity
{
public:
	float X, Y;
	void Move(float xa, float ya)
	{
		X += xa;
		Y += ya;
	}
};

//public表示子类继承的父类的成员变量/方法，
//最高只能是public。如果是class Player :protected Entity
//则原来父类中的public成员变量变成protected，但是原来的protected
//和private成员变量则不变
class Player :public Entity
{
public:
	const char* Name;

	void PrintName()
	{
		std::cout << Name << std::endl;
	};
};
int main()
{

	std::cin.get();
}