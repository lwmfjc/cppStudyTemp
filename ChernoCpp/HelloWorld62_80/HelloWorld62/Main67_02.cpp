#ifdef LY_EP67_
#include <iostream>

struct Vector2
{
	float x, y;
};

struct Vector4
{
	float x, y, z, w;

	Vector2& GetA()
	{
		//把&x当成一个Vector2的地址来解释
		//*表示取值的时候连续取两个float的值来构成一个Vector2
		return *(Vector2*)&x;
	}

	//尝试把Vector4看成是两个Vector2
	//Vector2 GetA()
	//{
	//	//..
	//	//添加一些成员并返回，这里省略了
	//	return Vector2();
	//}
};

void PrintVector2(const Vector2& v)
{
	std::cout << "Vector2: (" << v.x << ", " << v.y << ")\n";
}

int main()
{
	std::cin.get();
}
#endif