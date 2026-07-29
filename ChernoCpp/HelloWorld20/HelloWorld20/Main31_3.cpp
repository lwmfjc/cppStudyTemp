#ifdef LY_EP31_3


#include <iostream>
#include <string>

//不要用这种形参，这会在使用时另外增加一个string副本
void PrintString(std::string string) {
	string += "h";
	std::cout << string << std::endl;
}

//推荐
void PrintStringRight(const std::string& string) {
	//报错
	//string += "h";
	std::cout << string << std::endl;
}

int main()
{
	//std::string 内部通常包含一个字符指针（指向字符数据的指针）
	//"Cherno"->"const char[7]"
	//std::string name = "Cherno";
	//std::cout << name << std::endl;
	//std::cout << name.size() << std::endl;//6

	////把两个字符串相加,下面这句会报错
	////std::string name2 = "Cherno" + "_hello";
	////这里+,+= 被 std::string重载了
	//name = name + "_hello";
	//name += "_hello";
	////编译通过
	//std::string name3 = std::string("Cherno") + "_hello";

	////std::string::npos 是一个特殊常量，表示 "未找到" 或 "无效位置"。
	//bool contains = name.find("no") != std::string::npos;

	std::string name = std::string("Cherno") + "_hello";
	PrintString(name);//Cherno_helloh
	std::cout << name << std::endl;//Cherno_hello
	PrintStringRight(name);

	std::cin.get();
}



#endif