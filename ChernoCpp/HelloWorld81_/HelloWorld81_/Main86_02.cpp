#ifdef LY_EP86

#include <iostream>     

template<typename T>
class ScopedPtr
{
public:
	ScopedPtr() = default;
	ScopedPtr(T* ptr) : m_Ptr(ptr) {}
	~ScopedPtr() { delete m_Ptr; }

	//指针是否有效
	bool IsValid() const { return m_Ptr != nullptr; }

	//把对象实例转为bool类型，判断指针是否有效
	/*explicit*/ operator bool() const { return IsValid(); }

	T* Get() { return m_Ptr; }
	const T* Get() const { return m_Ptr; }

private:
	T* m_Ptr = nullptr;
};

struct Entity
{
	float X = 0.0f, Y = 0.0f;
};

void ProcessEntity(const ScopedPtr<Entity>& entity)
{
	if (entity) //隐式调用 operator bool()
	{
		std::cout << "Entity position: (" << (*(entity.Get())).X << ", " << (*(entity.Get())).Y << ")" << std::endl;
	}
	else
	{
		std::cout << "Invalid entity pointer." << std::endl;
	}
}

int main()
{
	//隐式调用ScopedPtr(T* ptr)构造函数创建ScopedPtr对象
	ScopedPtr<Entity> e = new Entity();
	ProcessEntity(e); //输出 Entity position: (0, 0)

	/* std::unique_ptr源码 
	    explicit operator bool() const noexcept {
        return get() != nullptr;
    }
	*/
	std::unique_ptr<Entity> e(new Entity());
	//因为独占指针也可以转换为bool类型 
	ProcessEntity(e);

	std::cin.get();
	return 0;
}
#endif