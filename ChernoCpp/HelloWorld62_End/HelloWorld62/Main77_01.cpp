#ifdef LY_EP77

#include <iostream>
#include <variant>

int main()
{
	std::variant<std::string, int> data;
	data = "Cherno";
	std::cout << std::get<std::string>(data) << std::endl;
	data = 2;
	//data = 3.45;//编译报错，不通过
	std::cout << std::get<int>(data) << std::endl;
	//std::cout << std::get<std::string>(data) << std::endl;//运行时抛出异常
	data = true;//隐式转换，true转为1
	std::cout << std::get<int>(data) << std::endl;//1

	//运行时抛出异常
	//Unhandled exception at 0x763A2CA4 in HelloWorld62.exe: Microsoft C++ exception: std::bad_variant_access at memory location 0x012FFA2C.
	//std::cout << std::get<std::string>(data) << std::endl;

	//如上定义该变量时,std::string对应的索引映射为0，int对应的索引映射为1
	std::cout << data.index() << std::endl;

	//get_if函数接受一个地址，返回一个指针
	//如果当前 variant 存的数据类型匹配，它返回指向该数据的指针。
	//如果类型不匹配，它返回 nullptr（空指针），而不会让程序崩溃。
	if (auto  value = std::get_if<std::string>(&data))
	{
		std::string& v = *value;
		std::cout << "it's a string:" << v << std::endl;
	}
	else if (auto  value = std::get_if<int>(&data))
	{
		int& v = *value;
		std::cout << "it's an int:" << v << std::endl;

	}

	//union 的特点是所有成员共享同一块内存。如果你给 age 赋值，就会覆盖掉 name 的内存。如果此时 name 原本存有字符串，它的析构函数将无法正确释放内存，导致内存泄漏或崩溃。
	//注意：在现代 C++ 中，如果你要在 union 里放 std::string，你必须手动定义 union 的构造和析构函数。
	union TestS
	{
		std::string name;//28字节
		int age;//4字节
	};
	std::cout << "union======size===" << std::endl;
	std::cout << sizeof(std::string) << std::endl;//28字节
	std::cout << sizeof(int) << std::endl;//4字节
	std::cout << sizeof(TestS) << std::endl;//28字节
	std::cout << "variant======size===" << std::endl;

	//32=28+4，所以基本上创建了struct，或者说用于存储两种数据类型的空间；所以union更高效，而variant安全性更高
	std::cout << sizeof(data) << std::endl;//32


	std::cin.get();
	return 0;
}
#endif