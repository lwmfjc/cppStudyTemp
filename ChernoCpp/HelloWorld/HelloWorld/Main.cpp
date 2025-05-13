#include <iostream>
//（编译器处理）include是预处理指令，
// 会在编译前找到iostream这个文件并插入该文件内容
// .h文件是在预编译时被处理（插入），并不会被编译；只有
// .cpp文件会被编译成 .obj文件，链接器把这些合并成 .exe文件

int main() {
	// << 重载运算符, 运算符可以理解成函数
	//类似 std::cout.print("hello world").println()
	std::cout << "hello world!" << std::endl;
	//等待接收字符
	std::cin.get();
	//可以不写return，默认返回0，表示正确返回程序
}