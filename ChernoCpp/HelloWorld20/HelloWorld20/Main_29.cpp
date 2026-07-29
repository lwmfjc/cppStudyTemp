#ifdef LY_EP29

#include <iostream>
#include <string> 

class Entity 
{ 
//private意味着只有Entity类及其子类里面可以直接读取它们，
//(其他外部的类[比如main()]也不行)
//例外：友元函数可以读取一个类的protected成
// 员[友元函数是普通函数，不是类的成员]
protected :
	int X, Y;
	void Print() {}
public :
	Entity()
	{
		X = 0;
		Print();
	}
};

class Player :public Entity
{ 
public:
	Player()
	{
		Print();

	}
}; 
 

int main()
{

	Entity e;
	//e.Print();//报错
	std::cin.get();

	std::cin.get();
}

#endif