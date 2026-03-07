#ifdef LY_EP82_

#include <iostream>  


class Random
{
public:

	//禁止拷贝
	Random(const Random&) = delete;

	////禁止赋值
	//赋值运算符：用于更新一个已存在的对象
	/*
	Random r1; // 假设某种情况下你已经有了一个实例（比如在类内部）
	r1 = Random::Get(); // 这会调用赋值运算符
	*/
	Random& operator=(const Random&) = delete;

	static Random& Get()
	{
		//函数里的静态变量，在静态内存中
		//一旦get函数首次被调用，它就会被实例化，然后
		//在后续调用中，它就一直存在于静态内存中
		static Random s_Instance;
		return s_Instance;
	}
	static float Float()
	{
		return Get().IFloat();
	}
private:

	float IFloat() {
		return m_RandomGenerator;
	}

	float m_RandomGenerator = 0.5f;
	Random() {}


};


int main()
{
	//先内联Float变成Random::Get().IFloat();
	//之后内联Get和IFloat变 Random::s_Instance.m_RandomGenerator
	//最后这里还进行常量折叠 float number = 0.5f;
	float number = Random::Float();

	std::cout << number << std::endl;

	std::cin.get();
	return 0;
}
#endif