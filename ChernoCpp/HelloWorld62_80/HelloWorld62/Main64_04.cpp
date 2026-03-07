#ifdef LY_EP64_
#include <iostream>

int main()
{
	//这是一个栈上的原生二维数组,且内存中连续(对比int** a2d = new int* [5];方式)
	//物理形态：[ 1, 2, 3, 4, 5, 6, 7, ... 25 ] 
	//特点：编译器通过公式 Address + (row x 5 + col) x 4 直接定位。没有额外的寻址操作。(字节定位)
	int a[5][5] = { 1,2,3,4,5,6,7,8,9,10, 11,12,13,14,15,16,17,18,19,20, 21, 22, 23, 24, 25 };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			std::cout << a[i][j] << std::endl;


	//使用一维数组(连续的一块内存)完成二维数组5 * 5 的数组功能
	int* array = new int[5 * 5];
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			array[x + y * 5] = 2;
		}
	}

	std::cin.get();
}

#endif;