#include <iostream>
#include <memory>
class Entity
{
public:

	//constructor-构造函数
	Entity()
	{
		std::cout << "Created Entity!" << std::endl;
	}


	//destructor-析构函数
	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print()
	{
		std::cout << "hello" << std::endl;
	}

};
int main() {
    std::weak_ptr<Entity> observer;

    {
        std::shared_ptr<Entity> entity = std::make_shared<Entity>();
        observer = entity; // observer 记住了这个 entity

        // 此时 entity 还在
        if (auto locked = observer.lock()) { // lock() 尝试转成 shared_ptr
            std::cout << "对象还在，正在调用 Print...\n";
            locked->Print();
        }
    } // 出了这个大括号，entity 被销毁了

    // 此时 entity 已经不在了
    if (auto locked = observer.lock()) {
        locked->Print();
    }
    else {
        std::cout << "对象已经销毁了，无法调用！\n";
    }
    std::cin.get();
    return 0;
}
/*
Created Entity!
对象还在，正在调用 Print...
hello
Destroyed Entity!
对象已经销毁了，无法调用！
*/