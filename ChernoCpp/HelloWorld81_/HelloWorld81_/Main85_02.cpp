#ifdef LY_EP85_

#include <iostream>  
#include <string>
 

void PrintName2(std::string&& name)
{
	std::cout << "PrintName2[rvalue:]" << name << std::endl;
}

//const引用，能和右值兼容，既能接受左值，也能接受右值
void PrintName2(const std::string& name)
{
	std::cout << "PrintName2[const lvalue:]" << name << std::endl;
}

void PrintName1(std::string&& name)
{
	std::cout << name << std::endl;
}

void PrintName(std::string& name)
{
	std::cout << name << std::endl;
}

int main()
{ 
	//左值：firstName和lastName是左值，fullName是左值
	//右值：字符串字面值"Yan"和"Chernikov"是右值，firstName + lastName是右值
	// firstName + lastName构建一个临时对象，然后赋值给左值fullName 
	std::string firstName = "Yan";
	std::string lastName = "Chernikov";

	std::string fullName = firstName + lastName; 

	//非const的左值引用只能用左值来初始化，所以也可以用
	//这个函数来测试一个表达式是否是左值
	PrintName(fullName);
	//PrintName(firstName + lastName);//编译报错，非const的左值引用必须用左值来赋值

	//PrintName1(fullName);//编译报错，右值引用不能绑定到左值(必须用右值来赋值)
	PrintName1(firstName + lastName);

	PrintName2(firstName);

	//优先调用void PrintName2(std::string&& name)这个重载版本
	PrintName2(firstName + lastName);

	std::cin.get();
	return 0;
}
#endif