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
//	//这里e1不增加引用计数，所以
//	std::weak_ptr<Entity> e1;
//	std::cout << "start--" << std::endl;
//	{
//		std::cout << "start0--" << std::endl;
//		std::shared_ptr<Entity> e0;
//		{
//			std::cout << "start1--" << std::endl;
//			std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
//			e1 = sharedEntity;
//			e0 = sharedEntity;
//			std::cout << "end1--" << std::endl;
//		}
//		//至此sharedEntity已经被回收，但是e0还在
//		std::cout << "end0--" << std::endl;
//	}
//	//至此e0已经被回收，所有的指向Entity对象的引用都被回收了，e1虽然没有被回收但是它不增加引用计数，所以Entity对象被回收
//	std::cout << "end--" << std::endl;
//	std::cin.get();
//}
///* end0打印后，Entity对象才被回收
//start--
//start0--
//start1--
//Created Entity!
//end1--
//end0--
//Destroyed Entity!
//end--
//*/