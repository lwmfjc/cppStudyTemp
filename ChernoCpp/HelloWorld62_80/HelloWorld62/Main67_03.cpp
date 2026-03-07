#ifdef LY_EP67_
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

		//union的大小，是它内部最大的成员的大小。在这个例子中，union的大小是16字节（4个float，每个4字节）。

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

	//可以用vector.x,vector.y,vector.z,vector.w来访问这四个float
	//或者用vector.a和vector.b来访问这两个Vector2
	//且vector.a.x和vector.a.y分别对应vector.x和vector.y，vector.b.x和vector.b.y分别对应vector.z和vector.w(
	//因为它们共享同一块内存，所以修改其中一个成员会影响到其他成员的值)
	vector.x = 2.0f;
	std::cout << "Vector4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")\n";// Vector4: (2, 2, 3, 4)

	//验证上述结论
	//这里修改了z却间接修改了vector.b
	vector.z = 500.0f;
	std::cout << "-----" << std::endl;

	PrintVector2(vector.a); // Vector2: (2, 2)
	PrintVector2(vector.b); // Vector2: (500, 4)
	std::cin.get();
}
#endif