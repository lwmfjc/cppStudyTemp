#include <iostream>
#include <string> 

//类型别名 (Type Alias) 声明。
using String = std::string;

// using 声明，使用的时候只能用string(只起到了省略std::的作用)
//using std::string; 

/*
- 如果你把"using String = ... 还是 using std::string;"写
在 .h (头文件) 的全局作用域里，都会产生“污染”：
- 任何 #include 你这个头文件的人，都会被强制接受你的命名习惯。
如果别人也定义了一个 String，代码就会崩溃（冲突）。
*/

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
	//在堆上创建对象（这里会默认调用默认构造函数）
	Entity entity;
	std::cout << entity.GetName() << std::endl;

	std::cin.get();
}