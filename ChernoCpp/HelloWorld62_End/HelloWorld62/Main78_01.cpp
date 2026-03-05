#ifdef LY_EP78_

#include <iostream> 
#include <any>
#include <string>
#include <variant>

int main()
{
	std::any data;
	{
		char name[] = "Cherno";
		data = (const char*)name;// 将 name 数组的地址存储在 data 中

	} // name 数组在这里被销毁了

	// 此时 data 内部存储的指针指向了一个已经失效的内存地址（野指针）

	data = 3.45;

	//1. 构造临时对象：std::string 首先根据 "Cherno" 构造自己（这次会有一次内存分配和拷贝）。
	//2. 调用 operator=：这个临时对象被传给 std::any::operator=。
	//3. 内部转换：std::any 内部会检测到这是一个右值（临时对象），它会调用 std::string 的移动构造函数，在自己的内部空间（或它在堆上新开辟的空间）重建这个 string。
	//4. 释放临时对象：原本的临时对象变成“空壳”，随后被销毁。
	data = std::string("Cherno");// 现在 data 内部存储的是一个 std::string 对象，之前的指针已经被覆盖了

	// 这种方式直接在 data 的内部空间构造 string，效率最高
	data = std::make_any<std::string>("Cherno");

	//获取值
	std::string string = std::any_cast<std::string>(data);
	std::cout << string << std::endl;

	data = "haha";

	//运行时报错,data此时是一个const char*，不是std::string
	//std::string string2 = std::any_cast<std::string>(data);
	//std::cout << string2 << std::endl;

	std::variant<int, std::string> var;
	var = 3;
	var = "Hello";

	std::string string3 = std::get<std::string>(var);
	std::cout << string3 << std::endl;//运行正常，输出"Hello"

	std::cin.get();
	return 0;
}
#endif