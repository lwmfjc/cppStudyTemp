#include "iostream"
#include "Log.h" 


int main()
{
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

	for (int i = 0; i < 5; i++)
	{
		if (i > 5)
			return 0;
		std::cout << i;
		Log("Hello world!");
	}

	std::cin.get();
}