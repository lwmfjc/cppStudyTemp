#pragma once
#include <memory>

template<typename T>
class Vector
{
public:
	Vector()
	{
		//allocate 2 elements
		ReAlloc(2);
		std::cout << "====构造器中初始化容量2======" << std::endl;
	}

	void PushBack(const T& value)
	{
		//如果当前数量量已经大于等于容量
		if (m_Size >= m_Capacity)
		{
			//如果增长，容量扩大为1.5倍
			ReAlloc(m_Capacity + m_Capacity / 2);
		}

		m_Data[m_Size] = value;
		m_Size++;
		std::cout << "添加元素:" << value << std::endl;
		std::cout << "==================" << std::endl;
	}

	T& operator[](size_t index)
	{
		if (index >= m_Size)
		{
			//assert
		}
		m_Data[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= m_Size)
		{
			//assert被设计为一种调试期工具,在发布版本会被去掉
			//assert
		}
		return m_Data[index];
	}

	size_t Size() const { return m_Size; }

private:
	void ReAlloc(size_t newCapacity) {
		// 1. allocate a new block of memory
		// 2. copy/move old elements into new block
		// 3. delete

		//尽可能低层次的访问内存，而不是智能指针
		//在堆上申请了一块连续(物理连续)的内存空间
		T* newBlock = new T[newCapacity];

		//如果新容量小于当前大小，即缩小容量
		if (newCapacity < m_Size)
		{
			// 当前大小设置为新容量大小
			m_Size = newCapacity;
			std::cout << "缩小容量--" << std::endl;
		}
		else
		{

			std::cout << "增大容量--" << m_Capacity << "->" << newCapacity << std::endl;
		}

		for (size_t i = 0; i < m_Size; i++)
		{
			//不会触发复制构造函数
			//memcpy(newBlock, m_Data, i * sizeof(T);

			//复制,会触发复制构造函数
			newBlock[i] = m_Data[i];
		}

		delete[] m_Data;//释放原来指向的内存块
		m_Data = newBlock;//指向新的那个内存块
		m_Capacity = newCapacity;

	}



	T* m_Data = nullptr;
	//实际数组个数
	size_t m_Size = 0;
	//可分配存储的元素个数
	size_t m_Capacity = 0;
};