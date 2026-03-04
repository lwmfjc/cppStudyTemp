#ifdef LY_EP76

#include <iostream>   
#include <fstream>
//C++17引入了std::optional类型，可以用来表示一个值可能存在也可能不存在的情况。它提供了一种更安全和更清晰的方式来处理函数返回值，避免了使用引用参数来传递成功与否的信息。
#include <optional>
#include <sstream> //读取文件内容需要使用std::stringstream


//方法1：通过引用参数返回成功与否
//std::string ReadFileAsString(const std::string& filePath,
//bool& outSuccess)
std::optional<std::string> ReadFileAsString(const std::string& filePath)
{
	std::ifstream stream(filePath);
	if (stream)
	{
		std::stringstream result;
		result << stream.rdbuf();
		//read file
		stream.close();
		return result.str();
	} 
	return {};
}

int main()
{

	//在内存中，std::optional<T> 通常包含两个主要部分：
	//1. 一块足够大的内存空间：用来存放类型为 T 的值（在你的例子中是 std::string）。
	//2. 一个布尔标记（bool flag）：记录这个盒子现在是“满的”还是“空的”
	std::optional<std::string> data = ReadFileAsString("data.txt");
	std::optional<std::string> data1 = ReadFileAsString("data1.txt");

	//如果是读取参数，那就是指定默认值
	//std::string value = data.value_or("default value");

	//或者if(data)
	if(data.has_value())
	{
		//数据读取
		std::string& string = *data;
		std::cout << "File content: " << data.value() << std::endl;
		std::cout << "File content: " << string << std::endl;
	}
	else
	{
		std::cout << "Failed to read file." << std::endl;
	}


	if (data1.has_value())
	{
		//数据读取
		std::string& string = *data1;
		std::cout << "File content: " << data1.value() << std::endl;
		std::cout << "File content: " << string << std::endl;
	}
	else
	{
		std::cout << "Failed to read file(data1.txt)." << std::endl;
	}
	std::cin.get();

} 
/*
File content: Data!Hello!
File content: Data!Hello!
Failed to read file(data1.txt).
*/
#endif