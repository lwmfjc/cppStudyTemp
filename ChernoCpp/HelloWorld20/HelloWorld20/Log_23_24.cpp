#ifdef LY_EP23_24
#include <iostream>

class Log
{
public:
	enum Level
	{
		//这里不能用Error，因为下面有一个同名函数
		LevelError=0, LevelWarning, LevelInfo
	}; 
private:
	//日志实际级别
	//m开头表示类成员变量
	Level m_LogLevel = LevelInfo;
public:
	void SetLevel(Level level)
	{
		m_LogLevel = level;
	}

	//关于字符串指针，后面会讲解
	void Error(const char* message)
	{
		//因为枚举类型是整型，所以
		//这里可以比较
		if (m_LogLevel >= LevelError)
			std::cout << "[ERROR]:" << message << std::endl;
	}

	void Warn(const char* message)
	{
		if (m_LogLevel >= LevelWarning)
			std::cout << "[WARNING]:" << message << std::endl;
	}

	void Info(const char* message)
	{
		if (m_LogLevel >= LevelInfo)
			std::cout << "[INFO]:" << message << std::endl;
	}
};
 
//int main()
//{
//	Log log;
//	//警告或更严重的消息会被打印出
//	log.SetLevel(Log::LevelWarning);
//	log.Warn("Hello!");
//	log.Error("Hello!");
//	log.Info("Hello!");
//	/*
//	[WARNING]:Hello!
//	[ERROR]:Hello!
//	*/
//
//	std::cin.get();
//}

#endif
