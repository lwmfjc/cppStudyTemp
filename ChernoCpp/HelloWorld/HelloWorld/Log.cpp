/*试着编译单个cpp文件 ctrl+f7
会生成Log.obj文件*/

//如果没有这句，会提示cout不是std的成员，因为
//没有包含这样函数的声明
#include <iostream>


//定义，定义这个函数到底是什么
void Logr(const char* message) {
	std::cout << message << std::endl;
}