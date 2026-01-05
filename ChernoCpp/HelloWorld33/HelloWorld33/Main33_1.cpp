//#include <iostream>
//
//int main()
//{
//	//当你定义 const int MAX_AGE = 90; 时，编译器通常会进行常量折叠（Constant Folding）。这意味着在编译阶段，代码中所有出现 MAX_AGE 的地方都会被直接替换为数字 90;
//	//所以最下面的 std::cout << MAX_AGE << std::endl; 打印90
//	const int MAX_AGE = 90;
//	std::cout << MAX_AGE << std::endl;//90
//
//	int* a = new int;
//
//	*a = 2;
//	std::cout << *a << std::endl;//2
//
//	//如果不加 (int*)类型强转,提示 a value of type "const int *"cannot beassigned to an entity of type "int *"
//	//报错原因：1. 如果你能直接把 const int* 赋值给 int*，那么你就可以通过 *a = 100; 来修改 MAX_AGE 的值。这违背了 const 的初衷。为了保证代码的健壮性，编译器禁止这种**“权限扩大”**的行为（从“只读”变成“可读写”）。
//	//	2. 为什么加上(int*) 就不报错了？
//	//	当你加上(int*) 时，你正在使用强制类型转换（C - style Cast）。
//	//	这相当于你对编译器说：“我知道 MAX_AGE 是常数，我也知道我在把只读指针转成可读写指针，出了问题我负责，请闭嘴。” 编译器接收到了你的强制指令，于是停止报错。
//	a = (int*)&MAX_AGE;
//	std::cout << *a << std::endl;//90
//	*a = 5;
//	std::cout << MAX_AGE << std::endl;//90
//	//MAX_AGE 对应的内存空间，通过指针非法修改成了 5
//	std::cout << *a << std::endl;//5
//
//	std::cin.get();
//}