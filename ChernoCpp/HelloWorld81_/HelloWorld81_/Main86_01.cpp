#ifdef LY_EP86_
 
#include <iostream>    
struct Orange
{
	operator float() const
	{
		return 3.14f;
	}
};

void PrintFloat(float value)
{
	std::cout << "PrintFloat(): " << value << std::endl;
}
 
int main()
{ 
	Orange orange;
	float f = orange; //隐式转换，调用 operator float()

	std::cout << f << std::endl; // 输出 3.14
	std::cout << (float)orange << std::endl; // 输出 3.14
	PrintFloat(f);//orange先隐式转换成float

	std::cin.get();
	return 0;
}
/*  
*/
#endif