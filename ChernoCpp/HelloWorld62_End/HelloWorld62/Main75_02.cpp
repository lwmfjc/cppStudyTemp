#ifdef LY_EP75

#include <iostream>  
#include <string>
#include <tuple>

//或者使用std::pair<std::string, int> CreatePerson()
//tuple可以存储任意数量和类型的元素，而pair只能存储两个元素，分别是first和second。
std::tuple<std::string, int> CreatePerson()
{
	return { "Cherno",24 };
}
 

int main()
{
	auto[name, age] = CreatePerson();
	std::cout << "name:" << name <<   "--age:" <<
		age << std::endl;
	std::cin.get();

}
/*
name:Cherno--age:24
*/
#endif