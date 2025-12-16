#include <iostream>
#include "Log.h"

void InitLog() {
	Log("initialized");
}

void Log(const char* message) {
	std::cout << message << std::endl;
}