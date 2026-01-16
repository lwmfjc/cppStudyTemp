//#include <iostream>
//#include <string>
//
//struct Vector2
//{
//	float x, y;
//};
//
//int main()
//{
//	int a1 = 2;
//	int b1 = a1;
//	//a，b是两个不同的变量，互不影响
//	b1 = 3;
//	std::cout << a1 << std::endl;//2
//	std::cout << b1 << std::endl;//2
//
//	Vector2 a = { 2,3 };
//	Vector2 b = a;
//	b.x = 5;
//	std::cout << a.x << std::endl;//2
//	std::cout << b.x << std::endl;//5
//
//	Vector2* aP = new Vector2();
//	//复制了指针，没有复制实际数据
//	Vector2* bP = aP;
//	bP->x = 2;
//	std::cout << aP->x << std::endl;//2
//	std::cout << bP->x << std::endl;//2
//
//	bP++;//aP没有被影响到
//	std::cout << aP << std::endl;//000002A2946D9EC0
//	std::cout << bP << std::endl;//000002A2946D9EC8
//
//
//
//	std::cin.get();
//	return 0;
//}