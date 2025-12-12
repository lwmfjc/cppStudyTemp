/*试着编译单个cpp文件 ctrl+f7
会生成Main.obj文件*/

/*/①（编译器处理）include是预处理指令，会在编
译前找到iostream这个文件并插入该文件内容*/
#include <iostream>


/*②.h文件是在预编译时被处理（插入），并不会被编译；只有
.cpp文件会被编译成 .obj文件，链接器把这些合并成 .exe文件*/

/*③声明，确实有Log函数存在*/
/*④链接器，编译整个项目时，(main中调用了该Log函数才会去链接)链接器链接时
才会去查找这个函数是否真是存在,如果不存在，则会提示"unresolved external
symbol"：未解析的外部符号，链接器无法找到定义---链接器的工作是将函数体链
接到其标识符(名称)
*/
//参数名message可以省略
void Log(const char* message);


int main() {
	// << 重载运算符, 运算符可以理解成函数
	//类似下面这句：
	// std::cout.print("hello world!").print(std:endl);//!!编译无法通过
	
	//std::cout << "hello world!" << std::endl;
	
	//演示Log函数
	Log("helloworld!");
	
	//等待按下回车键来移动到程序的下一行
	std::cin.get();
	//可以不写return，默认返回0，表示正确返回程序
}