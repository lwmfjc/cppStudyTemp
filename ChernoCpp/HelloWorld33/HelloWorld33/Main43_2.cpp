//#include <iostream>  
//#include <string>
//#include <memory>
//
//class Entity
//{
//public:
//
//	//constructor-构造函数
//	Entity()
//	{
//		std::cout << "Created Entity!" << std::endl;
//	}
//
//
//	//destructor-析构函数
//	~Entity()
//	{
//		std::cout << "Destroyed Entity!" << std::endl;
//	}
//
//	void Print()
//	{
//		std::cout << "hello" << std::endl;
//	}
//
//};
//
//int main()
//{
//	std::cout << "start--" << std::endl;
//	{
//		//不允许，禁止隐式转换
//		//std::unique_ptr<Entity> entity =new Entity();
//		
//		//允许,直接调用构造函数，但是不建议
//		//如果创建完原始对象后发生了异常，没有来得及将它放到智能指针对象
//		//会导致不释放指针指向内存，导致内存泄漏
//		//std::unique_ptr<Entity> entity(new Entity());
//		
//		//不会有这问题，因为std::make_unique保证了创建对象和将其
//		// 放入智能指针是一个原子操作==，中间不会被其他逻辑插入，因
//		// 此它是异常安全的。
//		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
//
//		entity->Print();
//
//		std::unique_ptr<Entity> e2 = std::move(entity);//允许
//		//std::unique_ptr<Entity> e3 = entity;//不允许，编译报错
//		/*查看源码
//		* 复制构造函数和赋值操作符被删除
//			unique_ptr(const unique_ptr&)            = delete;
//			unique_ptr& operator=(const unique_ptr&) = delete;		
//		*/
//
//	}
//	std::cout << "end--" << std::endl;
//	std::cin.get();
//}
///*
//start--
//Created Entity!
//hello
//Destroyed Entity!
//end--
//*/