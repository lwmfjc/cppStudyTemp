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
	//强引用，没有共享指针对象
	Object* shareObj2;
};

int main() {
	{
		Manager manager;

		{
			std::shared_ptr<Object> shareObj1 = std::make_shared<Object>();

			//没有阻止作用域外shareObj1内部实例销毁
			manager.shareObj2 = shareObj1.get();

		}//代码块结束时，shareObj1内部的Object实例对象被销毁

		std::cout << "obj still alive?" << (manager.shareObj2 == nullptr ? "true" : "false") << std::endl; //这里答案是false，即不是nullptr，但是shareObj2指向的对象(shareObje1内部的Object实例)早就销毁了
	}

	std::cout << "obj still die?" << std::endl;;
	std::cin.get();
}
/*
object destroyed!
obj still alive?false
obj still die?
*/
#endif 