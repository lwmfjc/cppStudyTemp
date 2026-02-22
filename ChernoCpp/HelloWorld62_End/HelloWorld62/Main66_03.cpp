#ifdef LY_EP66_
#include <iostream>

struct Entity
{
	int x, y;
	 
	int* GetPosition()
	{
		//替换了复制的写法
		/*int* array = new int[2];
		array[0] = x; 
		array[1] = y;*/
		return &x;
	}
};

struct EmptyStr
{

};

int main()
{
	//聚合初始化（Aggregate Initialization）机制
	Entity e = { 5,8 };//05 00 00 00 08 00 00 00 
	Entity e1 = { 5 };//05 00 00 00 00 00 00 00
	Entity e2 = {};//00 00 00 00 00 00 00 00
	EmptyStr es = {};//00 空结构体但是也占用了一个字节

	int  x1 = e.x;

	//指针形式的原始地址
	//这是一个：指向一个整数的指针
	int* position = (int*)&e;

	std::cout << position[0] << "," << position[1] << std::endl;

	int y1 = e.y;

	// 1. (char*)&e: 
	// 将 e 的首地址强制看作 char* 指针。
	// 意义：因为 char 占用 1 字节，这能让指针的“步长”变为 1 字节，方便我们进行精确的地址加减。
	// 2. + 4: 
	// 在 char* 的基础上移动 4 个单位。
	// 意义：因为步长是 1，所以这里实际上是向后偏移了 4 个字节，跳过了第一个成员 x。
	// 3. (int*): 
	// 将偏移后的新地址再次强制转换回 int*。
	// 意义：告诉编译器：“从这个位置开始，请用 int 的滤镜来看待这块内存”。
	// 4. *: 
	// 对 int* 进行解引用。
	// 意义：从当前偏移后的地址起，一口气读取 4 个字节，并将其作为整数赋值给 y。
	int y = *(int*)((char*)&e + 4);

	std::cout << y << std::endl;

	//得到一个有两个元素的实际整型数组
	int* position1 = e.GetPosition();
	std::cout << position1[0] << std::endl;
	std::cout << position1[1] << std::endl;

	std::cin.get();
}
#endif