#include <iostream>
#include <string> 

//类型别名 (Type Alias) 声明。
using String = std::string;

class Entity
{
private:
	String m_Name;
public:
	Entity() :m_Name("Unknown") {}
	Entity(const String& name) :m_Name(name) {}

	const String& GetName() const { return m_Name; }
};

int main()
{
	int a = 2;
	int* b = new int;
	//连续的50个元素(200个字节)
	int* b_arr = new int[50];

	Entity* e1 = new Entity;
	//和上面那句一个意思
	Entity* e2 = new Entity();

	
	//为了在执行 delete[] e_arr 时知道要调用多少次析构函数，
	// 编译器通常会在分配的内存块头部额外存储一个计数
	// 器（Cookie），记录数组的长度。
	//e_arr指向内存块的大小：50 * sizeof(Entity) + sizeof(size_t)
	//size_t是 C++ 中专门用来表示内存大小和索引的类型:64位系统中是8字节，
	//32位系统中是4字节
	//连续的50个Entity
	Entity* e_arr = new Entity[50];

	std::cin.get();
}