//没有这行会提示error C2039: 'cout': is not a member of 'std'
#include <iostream>
void Log(const char* message) {
	std::cout << message << std::endl;
}