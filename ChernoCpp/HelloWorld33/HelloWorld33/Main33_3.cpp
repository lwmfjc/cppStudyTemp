#include <iostream>

class Entity
{
private:
	int m_X, m_Y;
	int m_X1;
	mutable int var;
public:

	int GetX1()  
	{
		return m_X1;
	}

	int GetX() const
	{
		//var是一个mutable变量,在const方法中可以修改它
		var = 3;
		return m_X;
	}

	void SetX(int x)
	{
		m_X = x;
	}
};

void PrintEntity1(const Entity* e)
{
	e = nullptr;//允许编译，允许指向其他
	//(*e).SetX(2);//报错，不允许修改值
	std::cout << (*e).GetX() << std::endl;
}

void PrintEntity2(const Entity& e)
{
	//e = nullptr;//不允许编译，因为是引用，不允许重新指向其他
	//e.SetX(2);//报错，不允许修改值
	std::cout << e.GetX() << std::endl;
	//不允许调用非const修饰的函数，下面会报错,
	//因为无法保证GetX1()是否修改了e，而e是const修饰的
	//std::cout << e.GetX1() << std::endl;
}

int main()
{

	std::cin.get();
}