#include "iostream"
#include "Log.h" 


int main() {
	//InitLog();
	int a = 257;
	a++;
	const char* string = "Hello";
	for (int i = 0; i < 5; i++) {
		const char c = string[i];
		std::cout << c << std::endl;
	}
	Log("hello world!");
	//std::cin.get();
	std::cin.get();
}