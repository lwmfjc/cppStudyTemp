#ifdef LY_EP105_
#include <iostream>
#include <memory>

struct Object
{

	~Object()
	{
		std::cout << "object destroyed!" << std::endl;
	}
};

struct Manager
{
	std::shared_ptr<Object> shareObj2;
};

int main() {
	{
		Manager manager;

		{
			std::shared_ptr<Object> shareObj1 = std::make_shared<Object>();

			manager.shareObj2 = shareObj1;

		}//代码块结束时，shareObj1内部的Object实例对象并没有销毁

		std::cout << "obj still alive?" << std::endl;
	}
	//now obj still die,打印 object destroyed!

	std::cout << "obj still die?" << std::endl;;
	std::cin.get();
}
#endif
/*
obj still alive?
object destroyed!
obj still die?
*/