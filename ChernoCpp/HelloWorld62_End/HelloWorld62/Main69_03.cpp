#ifdef LY_EP69
#include <iostream>

void IncreaseValue(const int* val_ptr) {
	// 编译失败：不能修改 const 指针指向的内容
	//*val_ptr = 10; 

	// 使用 const_cast 去掉 const 属性
	int* modifiable_ptr = const_cast<int*>(val_ptr);
	*modifiable_ptr += 5;
}

int main() {

	//number 是一个普通的非 const 变量 
	int number = 10;

	std::cout << "修改前: " << number << std::endl;

	// 传入 number 的地址
	IncreaseValue(&number);

	std::cout << "修改后: " << number << std::endl; // 输出 15


	//=====演示有问题情况=====
	const int constant_var = 100; // 原始变量就是常量
	const int* ptr = &constant_var;

	int* naughty_ptr = const_cast<int*>(ptr);
	*naughty_ptr = 200; // 危险！这是“未定义行为”
	std::cout << "constant_var修改后: " << constant_var << std::endl;

	// 此时打印 constant_var，结果可能还是 100，也可能是 200，取决于编译器优化

	std::cin.get();
	return 0;
}
#endif