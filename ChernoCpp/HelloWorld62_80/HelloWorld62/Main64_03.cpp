#ifdef LY_EP64_
#include <iostream>

int main()
{ 
	//包含5个指针元素的数组
	int** a2d = new int* [5];
	 
	for (int i = 0; i < 5; i++)
	{ 
		//每个元素都包含五个数组
		a2d[i] = new int[5];
	} 

	//设置元素的值
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			a2d[y][x] = 2;
		}
	}

	//这25个元素并不是一个连续的能
	//容纳25个整数的缓冲区,而是5个独立
	//的缓冲区,每个缓冲区能容纳5个整数
	//这5个缓冲区,被分配到内存中的随机位置

	for (int i = 0; i < 5; i++)
	{
		//删除所有内部的数组
		delete[] a2d[i];
	}

	//这个删除的是,保存指针元素的那个数组(最外层)
	delete[] a2d;

	std::cin.get();
}

#endif;