#include <iostream>
#include "Log.h"
#include "Log.h"
#include "test.h"

void InitLog() {
	Log("Initializing Log");
}

void Log(const char* message) 
{
	std::cout << message << std::endl;
}