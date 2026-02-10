//#include <iostream>
//#include <string>
//
//std::string GetName1()
//{
//	return "Cherno";
//}
//
////返回值应该是const，修改项目设置后才能
//// 通过编译: c/c++-Language-Conformancemode-No
//char* GetName2()
//{
//	return "Cherno";
//}
//
//int main()
//{
//	auto a = 'a';
//
//	std::string name1 = GetName1();
//
//	//string有一个可接受字符指针的隐式构造函数
//	std::string name2 = GetName2();
//	name2.size();
//
//	//如果没有ide显示没办法一眼看出name3的类型
//	auto name3 = GetName2(); //char*
//	//name3.size();//显然这里编译会失败
//
//	std::cout << *name3 << std::endl;//"C"
//
//	std::cin.get();
//}