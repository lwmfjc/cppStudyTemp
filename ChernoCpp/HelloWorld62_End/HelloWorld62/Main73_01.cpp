#ifdef LY_EP73

#include <iostream> 

class Entity
{
public:
	virtual void PrintName() {}
};

class Player : public Entity
{
};

class Enemy : public Entity
{
};


int main()
{ 
	Player* player = new Player();
	Entity* e = player;//隐式转换，Player* 转换为 Entity*

	Entity* actuallyEnemy = new Enemy();
	Entity* actuallyPlayer = new Player();

	//Player* p = e;//错误，Entity* 转换为 Player*，需要显示转换

	Player* p = (Player*)actuallyEnemy;//不安全的转换，Enemy* 转换为 Player*，编译器允许，但运行时会出问题；如果访问Player和Entity共有的成员，可能不会出问题，但如果访问Player特有的成员，就会出问题，因为actuallyEnemy实际上是一个Enemy对象，而不是Player对象。

	Player* p1 = static_cast<Player*>(actuallyEnemy);//和上面的显示转换一样，属于不安全的转换 

	//actuallyEnemy指向的类必须是多态的，在 C++ 的设计哲学里，非多态类确实没有存储运行时的类型信息。
	Player* p2 = dynamic_cast<Player*>(actuallyEnemy);//安全的转换，运行时会检查actuallyEnemy是否实际上是一个Player对象，如果是，则返回指向Player对象的指针；如果不是，则返回nullptr。由于actuallyEnemy实际上是一个Enemy对象，所以p2将被赋值为nullptr。


	Player* p3 = dynamic_cast<Player*>(actuallyPlayer);

	if (p2)
	{
		std::cout << "actuallyEnemy is a Player." << std::endl;
	}
	else
	{
		std::cout << "actuallyEnemy is NOT a Player." << std::endl;
	}

	if(p3)
	{
		std::cout << "actuallyPlayer is a Player." << std::endl;
	}
	else
	{
		std::cout << "actuallyPlayer is NOT a Player." << std::endl;
	}

	std::cin.get();
}

/*
actuallyEnemy is NOT a Player.
actuallyPlayer is a Player.
*/
#endif