#ifdef LY_EP77

#include <iostream>
#include <variant>
#include <optional>
#include <fstream>
#include <sstream>

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

//使用variant修改为更合理的方案

enum class ErrorCode
{
	None = 0,
	FileNotFound = 1,
	PermissionDenied = 2,
	UnknownError = 3
};
 
//如果成功则获取值，如果失败则获取错误码
std::variant<std::string, ErrorCode> ReadFileAsString()
{
	//省略
	return {};
}

int main()
{ 
	std::cin.get();

	return 0;
}
#endif