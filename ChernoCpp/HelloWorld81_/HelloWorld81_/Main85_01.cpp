#ifdef LY_EP85

#include <iostream>   



void SetValueConst(const int& value)
{

}

void SetValue1(int& value)
{

}
void SetValue(int value)
{

}

int GetValue()
{
	return 10;//10是一个右值
}

int& GetRefValue()
{
	static int i=10;
	std::cout << "GetRefValue():" <<  i << std::endl; 
	return i;
}

int main()
{
	int i = 10;//i为左值，10为右值
	//10 = 3;//表达式必须为左值，10是右值，不能作为表达式的左边
	int a = i;//讲一个左值(a)设置为另一个左值(i)
	int i1 = GetValue();//GetValue()是一个右值，i是一个左值
	//GetValue() = 5;//GetValue()是一个右值，不能作为表达式的左边，而表达式必须是一个可修改的左值

	for (int i = 0; i < 3; i++)
	{
		GetRefValue()++;//GetRefValue()是一个左值，可以作为表达式的左边 

	}
	/*
GetRefValue():10
GetRefValue():11
GetRefValue():12
	*/

	SetValue(i);//i是一个左值，可以作为表达式的右边，用左值创建一个临时对象，并将其作为实参传递给函数
	SetValue(10);//10是一个右值，可以作为表达式的右边,即用右值创建一个临时对象，并将其作为实参传递给函数

	SetValue1(i);//从左值创建一个左值引用，所以可以将左值i作为实参传递给函数SetValue1(int& value)，编译器会将i作为实参传递给函数

	//SetValue1(10); //编译出错：不能从右值创建一个左值引用，所以不能将右值10作为实参传递给函数SetValue1(int& value)，编译器会报错 //非const的引用，必须通过左值来初始化

	SetValueConst(i);//从左值创建一个const左值引用 

	SetValueConst(10);//从右值创建一个const左值引用 
	//int& a1 = 10;//非const的引用，必须通过左值来初始化
	const int& b1 = 11;//const的引用，还可以通过右值来初始化

	std::cin.get();
	return 0;
}

/*

*/
#endif