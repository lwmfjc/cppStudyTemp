#include "iostream"
#include "Log.h" 
#define LOG(x) std::cout << x << std::endl;


//void Increment(int& value) { 
//	value++;
//}

//类定义
struct Player
{
	//默认是私有的
	//int x, y;
//这里的public包括了speed这个成员

	int x, y;
	int speed;
	//方法
	void Move( int xa, int ya)
	{
		x += xa * speed;
		y += ya * speed;
	}
};



int main()
{
	//player:对象
	//创建(实例化)一个对象
	Player player;
	player.x = 1;
	player.y = 2;
	player.speed = 2;
	player.Move( 1, -1);
	LOG(player.x);//3
	LOG(player.y);//0

	/*int a = 5;
	int b = 8;

	int* ref = &a;
	*ref = 2;
	ref = &b;
	*ref = 1;

	LOG(a);
	LOG(b);

	std::cin.get();*/


	//int x = 6;

	//比较这里比较int的4字节的
	// 每个位是否相等
	/*bool comparisionResult  = x == 5;
	if (comparisionResult)
	{
		Log("hello world!");
	}
	const char* ptr = "hello";
	if (ptr)
		Log(ptr);
	else if (ptr=="hello")
	{
		Log("ptr is hello!");
	}*/
	/*int i = 0;
	bool condition = true;
	for (; condition; ) {
		Log("Hello World");
		i = i + 1;
		if (!(i < 5))
			condition = false;
	}*/

	/*int i = 0;
	while (i < 5) {
		Log("Hello World");
		i++;
	}*/

	/*bool condition = false;
	while (condition)
	{

	}
	do
	{

	} while (condition);*/
	/*for (int i = 0; i < 2; i++)
	{

		std::cout << "i" << i << "-start" << std::endl;
		for (int j = 0; j < 2; j++) {

			std::cout << "j" << j << "-start" << std::endl;
			break;

			std::cout << "j" << j << "-end" << std::endl;
		}

		std::cout << "i" << i << "-end" << std::endl;
	}*/

	//for (int i = 0; i < 5; i++)
	//{
	//	if (i > 5)
	//		return 0;
	//	std::cout << i;
	//	Log("Hello world!");
	//}

	//int var = 8;

	//没有指定指针类型，编译器
	//不知道怎么存数据，*ptr=10会报错
	//void* ptr =  & var;
	//*ptr = 10;

	/*int* ptr = &var;
	*ptr = 10;
	LOG(var);*/

	/*char* buffer = new char[8];
	memset(buffer, 0, 8);
	
	char** ptr = &buffer;*/

	//int a = 5;
	//Increment(a);
	//std::cin.get();



	//int* b = &a;

	////&符号是类型的一部分
	////使用ref就跟使用a的别名一样
	//int& ref = a;
	////这里编译器编译后会直接设置a，而
	////不会再创建一个变量
	//ref = 2;

	//LOG(a);
	std::cin.get();
}