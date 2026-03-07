#ifdef LY_EP75_

#include <iostream>  
#include <string>
#include <tuple>

//或者使用std::pair<std::string, int> CreatePerson()
//tuple可以存储任意数量和类型的元素，而pair只能存储两个元素，分别是first和second。
std::tuple<std::string, int> CreatePerson()
{
	return { "Cherno",24 };
}


std::pair<std::string, int> CreatePerson1()
{
	return { "Cherno1",241 };
}

struct Person
{
	std::string name;
	int age;
};

Person CreatePerson2()
{
	return { "Cherno1",241 };
}

int main()
{
	auto person = CreatePerson();
	std::string& name = std::get<0>(person);
	int& age = std::get<1>(person);
	std::cout << "tuple: " << name << " is " << age << " years old." << std::endl;

	auto person1 = CreatePerson1();
	std::string& name1 = person1.first;
	int& age1 = person1.second;
	std::cout << "pair: " << name1 << " is " << age1 << " years old." << std::endl;

	std::string name11;
	int age11;
	std::tie(name11, age11) = CreatePerson();

	std::cout << "tuple with tie: " << name11 << " is " << age11 << " years old." << std::endl;

	std::string name12;
	int age12;
	std::tie(name12, age12) = CreatePerson1(); 

	std::cout << "pair with tie: " << name12 << " is " << age12  << " years old." << std::endl;

	auto person3 = CreatePerson2();
	std::cout << "struct: " << person3.name << " is " << person3.age << " years old." << std::endl;
	std::cin.get();

}
/*
tuple: Cherno is 24 years old.
pair: Cherno1 is 241 years old.
tuple with tie: Cherno is 24 years old.
pair with tie: Cherno1 is 241 years old.
struct: Cherno1 is 241 years old.
*/
#endif