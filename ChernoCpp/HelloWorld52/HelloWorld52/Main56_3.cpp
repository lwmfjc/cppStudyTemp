#include <iostream>
#include <string>
#include <vector>

//返回值应该是const，修改项目设置后才能
// 通过编译: c/c++-Language-Conformancemode-No
char* GetName()
{
	return "Cherno";
}

int main()
{
	std::vector<std::string> strings;
	strings.push_back("apple");
	strings.push_back("orange");

	//迭代器，是一个经过精心设计的类，内部最核心的成
	// 员通常就是一个指向容器中某个位置的指针
	for (std::vector<std::string>::iterator it = strings.begin();
		it != strings.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	std::cout << "======1=====" << std::endl;

	//类型过于冗长，用auto替代
	for (auto it = strings.begin();
		it != strings.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "======2=====" << std::endl;

	//类型别名 (Type Aliasing) [现代C++风格]：，支持模板别名（模板化using）
	using UIterator = std::vector<std::string>::iterator;

	//类型别名 (Type Aliasing) [传统C风格]
	typedef std::vector<std::string>::iterator TIterator;

	//类型过于冗长，用auto替代
	for (UIterator it = strings.begin();
		it != strings.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	std::cout << "======3=====" << std::endl;

	//类型过于冗长，用auto替代
	for (TIterator it = strings.begin();
		it != strings.end(); it++)
	{
		std::cout << *it << std::endl;
	}


	std::cin.get();
}