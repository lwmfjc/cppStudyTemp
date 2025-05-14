/*试着编译单个cpp文件 ctrl+f7
会生成Log.obj文件*/
#include <iostream>

//定义，定义这个函数到底是什么
void Log(const char* message) {
	std::cout << message << std::endl;
}