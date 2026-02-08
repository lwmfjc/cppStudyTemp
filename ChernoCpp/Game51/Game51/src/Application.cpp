#include <iostream>

//方法3，还要配合项目属性additional include directory
#include "Engine.h" //解决方案内的推荐用""
//#include <Engine.h> //如果是解决方案外的推荐用<>

//方法1
//#include "../../Engine/src/Engine.h"

//方法0
//namespace engine {
//	void PrintMessage();
//}


int main()
{

	engine::PrintMessage();
	std::cin.get();
}