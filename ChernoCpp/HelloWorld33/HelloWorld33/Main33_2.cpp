#include <iostream>

int main()
{
	const int MAX_AGE = 90;

	//不能修改指针指向的地址里的值(但可以修改指针指向)
	const int* a = new int;
	//int const* a = new int;//跟上一句一个意思,const都是在*前面
	//*a = 2;//报错

	//由于a已经是const int*了，
	//所以这里编译器没有像int* a时报错
	a = &MAX_AGE;

	std::cout << *a << std::endl;//90 

	//不能修改指针指向的地址里的值(但可以修改指针指向)
	int* const  b = new int;
	*b = 2; //可修改地址里的值
	//不可重新分配b指向其他地址
	//b = &MAX_AGE;//报错


	const int* const  c = new int;
	int const* const  d = new int;
	/*以下均编译不通过*/
	//*c = 2;
	//c = &MAX_AGE;
	//*d = 2;
	//d = &MAX_AGE;
	/*以上均编译不通过*/

	std::cin.get();
}