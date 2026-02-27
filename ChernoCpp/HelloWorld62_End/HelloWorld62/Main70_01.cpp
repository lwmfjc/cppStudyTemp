#ifdef LY_EP70
#include <iostream>

int main()
{ 
	int a = 2, b = 3;
	for (int i = 0; i < 5; i++) {
		std::cout << "i:" << i << std::endl;
	}
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cin.get();
	return 0;
}
#endif