#include "Engine.h"
#include <iostream>

namespace engine {
	void PrintMessage()
	{
		std::cout << "Hello World!" << std::endl;
	}
}

//或者这么写
//void engine::PrintMessage()
//{
//	std::cout << "Hello World!" << std::endl;
//}