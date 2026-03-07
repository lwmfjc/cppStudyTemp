#ifdef LY_EP82_

#include <iostream>  


namespace RandomClass {
	//在 namespace（或全局作用域）中，static 意味着“内部链接（Internal Linkage）”
	static float s_RandomGenerator = 0.5f;
	static float Float() {
		return s_RandomGenerator;
	}
}

int main()
{ 
	float number = RandomClass::Float();

	std::cout << number << std::endl;

	std::cin.get();
	return 0;
}
#endif