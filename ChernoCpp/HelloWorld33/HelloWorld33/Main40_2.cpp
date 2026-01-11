//#include <iostream>
//#include <string>   
//
//struct Vector2
//{
//	float x, y;
//
//	Vector2(float x, float y)
//		:x(x), y(y) {
//	}
//
//	Vector2 Add(const Vector2& other) const
//	{
//		//this是指向自身的一个指针
//		//return *this + other;
//
//		//或者
//		return operator+(other);
//	}
//
//	Vector2 operator+(const Vector2& other) const
//	{
//		return Vector2(x + other.x, y + other.y);
//	}
//
//	Vector2 Multiply(const Vector2& other) const
//	{
//		return Vector2(x * other.x, y * other.y);
//	}
//
//};
//
//int main()
//{
//	Vector2 position(4.0f, 4.0f);
//	Vector2 speed(0.5f, 1.5f);
//	Vector2 powerup(0.5f, 1.5f);
//
//	Vector2 result1 = position.Add(speed.Multiply(powerup));
//	Vector2 result2 = position + speed;// *powerup;
//
//
//
//	std::cin.get();
//}