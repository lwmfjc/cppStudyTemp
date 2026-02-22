#ifdef LY_EP67_
#include <iostream>
 

int main()
{
	struct Union
	{
		//在 C++ 中，如果你在一个 struct 或 class 内部定
		//义了一个_没有名字_的 union，编译器会把这个联合体
		//的成员直接注入（Injected）到外层结构体的作用域中。
		union
		{
			float a;
			int b;
		};
	};

	Union u;

	
	u.a = 2.0f;//0x00F6FE20  00 00 00 40
	//40 00 00 00 为 0100 0000 0000 0000 0000 0000 0000 0000
	//u.b：0表示正数，所以这个值为2^30次方，即 10,7374,1824 
	//也就是我们拿到了构成那个浮点数的内存，然后把它当做int来解释(
	//类型双关）
	std::cout << u.a << "," << u.b << std::endl;

	std::cin.get();
}
#endif