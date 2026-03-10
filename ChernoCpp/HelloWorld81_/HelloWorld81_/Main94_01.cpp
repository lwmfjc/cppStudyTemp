#ifdef LY_EP94

#include <iostream>   
#include <vector>
#include "94_01_vector.h"

int main()
{
	/*std::vector<int> values = { 1,2,3,4,5 };

	for (int i = 0; i < values.size(); i++)
	{
		std::cout << values[i] << std::endl;

	}

	for (int value : values)
	{
		std::cout << value << std::endl;
	}

	for (std::vector<int>::iterator it = values.begin();
		it != values.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	std::cout << "=============" << std::endl;*/

	Vector<int> values;
	values.EmplaceBack(1);
	values.EmplaceBack(2);
	values.EmplaceBack(3);
	values.EmplaceBack(4);
	values.EmplaceBack(5);

	std::cout << "Not using iterators:\n";
	for (int i = 0; i < values.Size(); i++)
	{
		std::cout << values[i] << std::endl;
	}

	std::cin.get();
	return 0;
}
#endif;