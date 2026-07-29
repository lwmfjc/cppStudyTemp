#ifdef LY_EP24

#include <iostream>

class Entity
{
public:
	//C++中不处理的话默认不初始化任何成员变量
	float X, Y;

	//默认的构造函数，什么都不做
	//不写任何构造函数是会默认添加这个
	//Entity()
	//{

	//}

	//构造函数
	Entity()
	{
		X = 0.00f;
		Y = 0.00f;
		std::cout << "Created Entity!" << std::endl;

	}

	//带参数的构造函数
	Entity(float x, float y) {
		X = x;
		Y = y;
	}


	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void  Print() {
		std::cout << X << "," << Y << std::endl;
	}
};

void Function()
{
	Entity e;//栈上分配
	e.Print();
}

int main()
{
	Function();
   /*
Created Entity!
0,0
Destroyed Entity!

   */

	std::cin.get();
}
#endif