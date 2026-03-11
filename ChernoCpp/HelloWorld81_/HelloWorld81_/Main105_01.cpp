#ifdef LY_EP105_
#include <iostream>
#include <memory>

class Entity {
public:
	Entity() { std::cout << "Entity Created" << std::endl; }
	~Entity() { std::cout << "Entity Destroyed" << std::endl; }
};

int main() {
	// --- unique_ptr 示例 ---
	{
		std::unique_ptr<Entity> e1 = std::make_unique<Entity>();
		// std::unique_ptr<Entity> e2 = e1; // 错误！禁止复制
		std::unique_ptr<Entity> e2 = std::move(e1); // 允许移动所有权，e1 现在为空
	} // e2 离开作用域，Entity 在这里被销毁

	std::cout << "-----------------" << std::endl;

	{
		// --- shared_ptr 示例 ---
		std::shared_ptr<Entity> sharedOuter;
		{
			//std::shared_ptr对象实例内部有一个引用计数，简单记录有多少个共享指针指向内部Entity对象的实例
			std::shared_ptr<Entity> sharedInner = std::make_shared<Entity>();

			sharedOuter = sharedInner; // 允许复制（拷贝赋值函数），引用计数变为 2
			std::cout << "Inner scope ending1..." << std::endl;
			std::shared_ptr<Entity> sharedInner1 = std::move(sharedOuter);//这里把sharedInner的所有权移走了，计数减一，但是本身又导致计数加一，所以目前是2 

			std::cout << "Inner scope ending2..." << std::endl;
		} // sharedInner1 离开作用域，sharedOuter所有权被移走，所以没有任何共享指针指向Entity了，  Entity 被销毁 

		std::cout << "Outer scope still holds Entity？" << std::endl;
	} //作用域结束，sharedOuter 离开作用域，Entity 最终在这里被销毁

	std::cin.get();
}
/*
Entity Created
Entity Destroyed
-----------------
Entity Created
Inner scope ending1...
Inner scope ending2...
Entity Destroyed
Outer scope still holds Entity？
*/
#endif