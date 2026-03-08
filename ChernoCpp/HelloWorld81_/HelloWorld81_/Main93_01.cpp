#ifdef LY_EP93_

#include <iostream>     
#include <vector>

//无序映射（哈希表）
#include <unordered_map>

int main()
{
	std::vector<int> values = { 1,2,3,4,5 };
	for (int i = 0; i < values.size(); i++)
	{
		//没有索引系统的集合类型，无法使用下标访问元素
		std::cout << values[i] << std::endl;
	}
	std::cout << "====0===" << std::endl;

	//基于范围的for循环
	for (int value : values)
	{
		std::cout << value << std::endl;
	}
	std::cout << "====1===" << std::endl;

	//values.end()返回一个超出可接受范围的迭代器对象，是个无效迭代器，是最后一个元素的下一个元素，所以不能访问它指向的元素
	//当你修改容器（添加、删除或重新分配内存）时，指向该容器元素的迭代器可能会变得像“野指针”一样，指向错误的内存地址。
	for (std::vector<int>::iterator it = values.begin(); it != values.end(); it++)
	{
		//像对待指针那样，进行解引用
		//因为实际的迭代器类里实现了类似星号的解引用操作符重载 
		std::cout << *it << std::endl;
	}
	std::cout << "====2===" << std::endl;
	using ScoreMap = std::unordered_map<std::string, int>;
	ScoreMap map;
	using ScoreMapConstIter = ScoreMap::const_iterator;
	map["Cherno"] = 5;
	map["c++"] = 2;

	//不修改容器中的元素时，使用const_iterator
	for (ScoreMapConstIter it = map.begin(); it != map.end(); it++)
	{
		//*it是一个pair对象，first成员是key，second成员是value
		//auto&，引用，不会实际复制值
		//迭代器指向的是 std::pair 类型
		auto& key = it->first;
		auto& value = it->second;
		std::cout << key << " " << value << std::endl;
	}
	std::cout << "====3===" << std::endl;
	//kv的类型: std::pair<const std:;string,int> &kv
	for (auto& kv : map)
	{
		auto& key = kv.first;
		auto& value = kv.second;
		std::cout << key << " " << value << std::endl;

	}
	std::cout << "====4===" << std::endl;

	//c++17才支持
	//C++17 的结构化绑定 (Structured Bindings)
	for (const auto& [key,value] : map)
	{ 
		std::cout << key << " " << value << std::endl;

	}

	std::cin.get();
	return 0;;
}
/*
1
2
3
4
5
====0===
1
2
3
4
5
====1===
1
2
3
4
5
====2===
Cherno 5
c++ 2
====3===
Cherno 5
c++ 2
====4===
Cherno 5
c++ 2
*/
#endif