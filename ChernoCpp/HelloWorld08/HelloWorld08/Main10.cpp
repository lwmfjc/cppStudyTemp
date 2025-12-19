#include "iostream"
#include "Log.h" 


int main() 
{
	int x = 6;
	
	//比较这里比较int的4字节的
	// 每个位是否相等
	bool comparisionResult  = x == 5;
	if (comparisionResult)
	{
		Log("hello world!");
	}
	const char* ptr = "hello";
	if (ptr)
		Log(ptr); 
	else if (ptr=="hello")
	{
		Log("ptr is hello!");
	}
	std::cin.get();
}