//#include <iostream>  
//#include <string>
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
//};
//
//int* CreateArrayWrong()
//{
//	//在栈上声明一个数组
//	//第一个元素为6，剩余49个为0
//	int array[50] = { 6 };
//	//返回指向该数组(栈内存)的指针
//	return array;
//}
//
//
//int* CreateArray1()
//{
//	//在栈上声明一个数组
//	//第一个元素为6，剩余49个为0
//	int* array = new int[50] { 6 };
//	//返回指向该数组(栈内存)的指针
//	return array;
//}
//void CreateArray2(int*)
//{
//	//填充数组
//}
//
//int main()
//{
//	//错误,这里得到的数据是不可信的，
//	//极有可能被其他代码拿来使用
//	int* a = CreateArrayWrong();
//
//	//方法1
//	int* a1 = CreateArray1();
//	//方法2
//	int array[50];
//	CreateArray2(array);
//
//	std::cin.get();
//}