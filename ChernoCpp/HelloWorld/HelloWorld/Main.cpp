#include <iostream>
//（编译器处理）include是预处理指令，
// 会在编译前找到iostream这个文件并插入该文件内容

int main() {
	std::cout << "hello world!" << std::endl;
	std::cin.get();
	//可以不写return，默认返回0
}