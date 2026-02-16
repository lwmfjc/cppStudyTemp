#ifdef LY_EP64_
#include <iostream>

int main()
{
	//创建一个数组,每个数组元素是指针
	int** a2d = new int* [50];

	//对50个元素赋值
	for (int i = 0; i < 50; i++)
	{
		//对第i个指针元素赋值,每个指针元素
		//指向新创建的数组
		a2d[i] = new int[50];

	}
	//第1个数组的第一个元素赋值为0
	//左边的0是指针的索引
	//右边的0,1,2是整数的索引
	a2d[0][0] = 0;
	a2d[0][1] = 0;
	a2d[0][2] = 0;

	//没有这种语法,编译报错
	//delete[][] a2d;


	for (int i = 0; i < 50; i++)
	{
		//删除所有内部的数组
		delete[] a2d[i];
	}
	//这个删除的是,保存指针元素的那个数组(最外层)
	delete[] a2d;

	std::cin.get();
}
#endif