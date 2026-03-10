#ifdef LY_EP92_

#include <iostream>   
#include <string>
#include "92_02_vector.h"


struct Vector3
{
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vector3() {}
	Vector3(float scalar)
		: x(scalar), y(scalar), z(scalar) {
	}
	Vector3(float x, float y, float z)
		: x(x), y(y), z(z) {
	}

	// 拷贝构造函数 (Copy Constructor)
	Vector3(const Vector3& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Copy\n";
	}


	//移动构造函数 (move Constructor)
	Vector3(Vector3&& other)
		: x(other.x), y(other.y), z(other.z)
	{
		std::cout << "Move\n";
	}

	//拷贝赋值
	Vector3& operator=(const Vector3& other)
	{
		std::cout << "copy=\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	//移动赋值
	Vector3& operator=(Vector3&& other)
	{
		std::cout << "move=\n";
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	~Vector3()
	{
		std::cout << "Destroy\n";
	}
};

//全局重载函数，C++ 规定：对于二元运算符（有两个操作数的运算符），如果写成全局函数，第一个参数对应运算符左边的对象，第二个参数对应右边的对象
std::ostream& operator<<(std::ostream& stream, const Vector3& v)
{
	stream << v.x << ", " << v.y << ", " << v.z;
	return stream;
}

void PrintVector(const Vector<Vector3>& vector)
{
	for (size_t i = 0; i < vector.Size(); i++)
	{
		std::cout << vector[i] << std::endl;
	}

	std::cout << "==================" << std::endl;
}

int main()
{
	Vector<Vector3> vector;

	//Vector3(1.0f)->创建一个匿名临时对象
	//临时对象会在包含它的那个“完整表达式（Full-expression）”结束时被销毁。即这行代码结束后该临时对象被析构
	vector.PushBack(Vector3(1.0f));

	vector.PushBack(Vector3{ 2,3,4 });
	vector.PushBack(Vector3{});


	PrintVector(vector);

	std::cin.get();
	return 0;
}
/*
增大容量--0->2
====构造器中初始化容量2======
move=
添加元素:1, 1, 1
==================
Destroy
move=
添加元素:2, 3, 4
==================
Destroy
增大容量--2->3
move=
move=
Destroy
Destroy
move=
添加元素:0, 0, 0
==================
Destroy
1, 1, 1
2, 3, 4
0, 0, 0
==================
*/
#endif