#include <iostream>
#include <string>

class Entity
{
public:
	void Print() const
	{
		std::cout << "Hello!" << std::endl;
	}
};

int main()
{
	Entity e;
	e.Print();

	//取消引用后用 .函数
	Entity* ptr = &e;
	Entity& entity = *ptr;
	entity.Print();
	(*ptr).Print();

	std::cin.get();
}