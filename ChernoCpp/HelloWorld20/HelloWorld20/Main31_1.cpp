//#include <iostream> 
//
//int main()
//{
//	//C风格的定义字符串的方式
//	//char* name = "Cherno";
//	//正常情况下不修改字符串的值,
//	//如果想要新的字符串，那么就要进行全新
//	//的内存分配并删除旧字符串(这里不是new，不
//	//需要手动delete)
//	const char* name = "Cherno";
//	char const* name1 = "Cherno";
//	//const在*前面，不允许修改数据
//	//name[2] = '1';//报错!
//	//name1[2] = '1';//报错!
//
//	char buffer[] = "Hello";
//	char* const  ptr = buffer;
//	//const在*后面，不允许指向另一个字符串
//	//ptr = new char[3] {'a','b','c'};//报错!
//
//	std::cin.get();
//}