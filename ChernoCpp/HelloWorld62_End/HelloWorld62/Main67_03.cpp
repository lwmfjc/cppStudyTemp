#ifdef LY_EP67
#include <iostream>

struct Vector2
{
	float x, y;
};

//最外层 struct Vector4：定义了这块内
// 存的总大小（4 x 4 = 16 字节）。
struct Vector4
{

	//这是一个“平行空间”。它(union)告诉编译器：“我内部定义的所有东西，都从同一个起始地址开始存放”。
	union  
	{


		//它把这 16 字节切分成了四个 float
		//，并分别取名为 x, y, z, w。(这个struct
		//是联合体的第1个成员）
		struct
		{
			float x, y, z, w;
		};

		//(这个struct是联合体的第2个成员）
		struct
		{
			Vector2 a, b;
		};

	};
};

void PrintVector2(const Vector2& v)
{
	std::cout << "Vector2: (" << v.x << ", " << v.y << ")\n";
}

int main()
{
	Vector4 vector = { 1.0f, 2.0f, 3.0f, 4.0f };
	vector.x = 2.0f;
	std::cout << "Vector4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")\n";// Vector4: (2, 2, 3, 4)
	std::cin.get();
}
#endif