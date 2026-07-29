#ifdef LY_EP32_4

#include <iostream>

int main()
{
	char name[] = "Cherno";
	name[2] = 'a';
	std::cout << name << std::endl;

	std::cin.get();
}



#endif