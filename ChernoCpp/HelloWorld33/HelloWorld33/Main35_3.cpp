#include <iostream>
#include <string>

class Example
{
public:
	Example()
	{
		std::cout << "Created Entity " << std::endl;

	}
	Example(int x)
	{
		std::cout << "Created Entity with " << x << std::endl;
	}
};

class Entity
{
private:
	std::string m_Name;
	Example m_Example;

public:

	Entity()
		:m_Name("Unkown"),m_Example(8)
	{

	}

	const std::string& GetName() const { return m_Name; }
};

int main()
{
	Entity e0;


	std::cin.get();
}