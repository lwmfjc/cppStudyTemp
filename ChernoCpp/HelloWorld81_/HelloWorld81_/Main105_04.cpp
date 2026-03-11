#ifdef LY_EP105
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
	//弱引用，可以用来共享指针对象但是不增加计数
	std::weak_ptr<Object> shareObj2;
};

int main() {
	{
		Manager manager;

		{
			std::shared_ptr<Object> shareObj1 = std::make_shared<Object>();

			//没有阻止作用域外shareObj1内部实例销毁
			//弱指针有一个接受共享指针的构造器
			manager.shareObj2 = shareObj1;

		}//代码块结束时，shareObj1内部的Object实例对象被销毁

		std::cout << "obj still alive?" << (manager.shareObj2.expired() ? "false" : "true") << std::endl; //这里答案是true，即shareObj2指向的对象(shareObje1内部的Object实例)早就销毁了

		//阻止了一种情况，就是检查后执行完//1之后，对象在其他线程中被
			//析构了
		//1. 由于 lock() 返回的是一个 shared_ptr（即代码中的 obj），根据 shared_ptr 的规则：
			//只要 obj 还在生命周期内（即在 if 分支的大括号 {} 里面），强引用计数至少为 1。
			//即使在执行 //1 或 //2 的瞬间，另一个线程销毁了 manager 里的原始 shared_ptr，对象也不会被析构。
		//2. 内存的释放被推迟到了 obj 离开作用域（大括号结束）的那一刻。
		if (auto obj = manager.shareObj2.lock())
		{

			//1
			//2
			
		}
		
		//检查是否存活
		if (manager.shareObj2.expired())
		{

		}

		//检查引用计数
		if (manager.shareObj2.use_count() == 0)
		{

		}
	}

	std::cout << "obj still die?" << std::endl;;
	 
	 
	std::cin.get();
}
/*
object destroyed!
obj still alive?true
obj still die?
*/
#endif 