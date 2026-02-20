#ifdef LY_EP66
#include <iostream>

struct Entity
{
	int x, y;
};

int main()
{
	int a = 50;
	//把a(内存处）的内存以double类型的方式进行访问
	//将整型进行类型双关变成双精度型
	//* 操作符会尝试从该地址开始，一口气往后读 8 个字节，这里是
	//32 00 00 00 cc cc cc cc （小端法）
	double  value = *(double*)&a;
	std::cout << a << std::endl;
	std::cout << value << std::endl;

	//不想创建全新变量，只是想把这个整数当成双精度数来访问，
	//那么可以在这个双精度数后面加&，这样就能引用他
	//强行让 value1 成为 &a 处那块 8 字节内存的别名。通过
	// value1 修改数据会直接破坏 a 及其相邻内存。
	double& value1 = *(double*)&a;
	//这里会把8个字节(a和a后面的4个字节)都写入0
	value1 = 0;
	std::cin.get();
}
#endif