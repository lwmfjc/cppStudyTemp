// 包括了全部
// #include <bits/stdc++.h>

// 1. 核心输入输出流
// （cin, cout）
#include <iostream>
// （printf, scanf）
#include <cstdio>

// 2. 常用 STL 容器（数据结构）
// （动态数组）
#include <vector>
// （字符串）
#include <string>
// （队列、优先队列 priority_queue）
#include <queue>
// （栈）
#include <stack>
// （键值对映射 / 哈希表）
#include <map>
#include <unordered_map>
// （集合）
#include <set>
#include <unordered_set>

// 3. 核心工具与算法
// （提供 sort, reverse, max, min, binary_search 等常用算法）
#include <algorithm>
// （数学函数，如 sqrt, pow, abs）
#include <cmath>
// （处理 C 风格字符串及内存操作，如 memset）
#include <cstring>

// 已移除 using namespace std;

int main()
{
  // 如果编译器能把一行代码解释成函数声明，它就绝对不会把它解释成对象创建。
  //  你的本意：创建一个默认的节点
  // TreeNode node1();
  //  ❌ 翻车！C++ 认为你在这里声明了一个名叫 node1、没有参数、返回值是 TreeNode 的函数！
  //  你的本意：创建一个默认的节点
  // TreeNode node2{};
  // 成功！C++ 明确知道这就是在调用无参构造函数创建对象。

  // ==========================================
  // 1. 核心输入输出与字符串 (<iostream>, <cstdio>, <string>)
  // ==========================================
  std::cout << "--- 1. 输入输出与字符串 ---" << std::endl;

  std::string s = "Hello";
  s += " World!"; // 字符串拼接
  std::cout << s << " Length: " << s.length() << std::endl;

  // C 风格打印（格式化输出非常方便，刷题时有时比 cout 更好控制小数点）
  int age = 18;
  std::printf("Age is %d, Pi is %.2f\n", age, 3.1415926);

  // ==========================================
  // 2. 常用 STL 容器 (<vector>, <stack>, <queue>)
  // ==========================================
  std::cout << "\n--- 2. 常用 STL 容器 ---" << std::endl;

  // Vector (动态数组，等价于 Java 的 ArrayList)
  std::vector<int> nums{10, 20, 30};                                  // 大括号初始化
  nums.push_back(40);                                                 // 末尾插入元素 (Java 的 add)
  std::cout << "Vector element at index 1: " << nums[1] << std::endl; // 支持下标访问

  // Stack (栈，后进先出)
  std::stack<int> st;
  st.push(1); // 压栈
  st.push(2);
  std::cout << "Stack top: " << st.top() << std::endl; // 查看栈顶：2
  st.pop();                                            // 弹出栈顶

  // Queue (队列，先进先出)
  std::queue<int> q;
  q.push(100);
  q.push(200);
  std::cout << "Queue front: " << q.front() << std::endl; // 查看队头：100
  q.pop();

  // ==========================================
  // 3. 哈希与集合 (<unordered_map>, <map>, <unordered_set>, <set>)
  // ==========================================
  std::cout << "\n--- 3. 哈希与集合 ---" << std::endl;

  // Unordered_map (哈希表，无序，等价于 Java 的 HashMap，O(1) 复杂度)
  std::unordered_map<std::string, int> mp;
  mp["Apple"] = 5;
  mp["Banana"] = 3;
  // 检查 key 是否存在 (C++20 新特性可用 contains，传统用 find)
  if (mp.find("Apple") != mp.end())
  {
    std::cout << "Apple count: " << mp["Apple"] << std::endl;
  }
  std::cout << "\n--- [mp]方法 2: C++11 范围 for 循环 ---" << std::endl;
  for (const auto &kv : mp)
  {
    std::cout << kv.first << ": " << kv.second << std::endl;
  }

  // Map (红黑树，按 key 自动升序排序，等价于 Java 的 TreeMap，O(log N))
  std::map<int, std::string> ordered_mp;
  ordered_mp[2] = "Two";
  ordered_mp[1] = "One"; // 虽然是后插入的，但会自动排在前面
  
  std::cout << "\n--- [ordered_mp]方法 2: C++11 范围 for 循环 ---" << std::endl;
  for (const auto &kv : ordered_mp)
  {
    std::cout << kv.first << ": " << kv.second << std::endl;
  }

  // Unordered_set (哈希集合，去重，O(1) 复杂度)
  std::unordered_set<int> my_set{1, 2, 2, 3}; // 自动去重
  std::cout << "Set size (should be 3): " << my_set.size() << std::endl;

  std::cout << "\n--- [my_set]方法 2: C++11 范围 for 循环 ---" << std::endl;
  for (const auto &kv : my_set)
  {
    std::cout << kv << std::endl;
  }

  // ==========================================
  // 4. 核心工具与算法 (<algorithm>, <cmath>, <cstring>)
  // ==========================================
  std::cout << "\n--- 4. 核心工具与算法 ---" << std::endl;

  // <algorithm> 常用算法
  std::vector<int> arr{5, 1, 4, 2, 8};
  std::sort(arr.begin(), arr.end());    // 排序：1, 2, 4, 5, 8
  
  std::cout << "\n--- [arr]方法 2: C++11 范围 for 循环 ---" << std::endl;
  for (const auto &kv : arr)
  {
    std::cout << kv << std::endl;
  }
  std::reverse(arr.begin(), arr.end()); // 反转：8, 5, 4, 2, 1
  
  std::cout << "\n--- [arr]方法 2: C++11 范围 for 循环 ---" << std::endl;
  for (const auto &kv : arr)
  {
    std::cout << kv << std::endl;
  }
  std::cout << "Max element: " << std::max(10, 20) << " Min element: " << std::min(10, 20) << std::endl;

  // <cmath> 数学函数
  // 注意：std::abs, std::sqrt, std::pow 在 <cmath> 中均有对应的 std:: 重载版本
  std::cout << "Sqrt of 16: " << std::sqrt(16) << std::endl;           // 开方：4
  std::cout << "2 to the power of 3: " << std::pow(2, 3) << std::endl; // 幂：8
  std::cout << "Absolute value of -5: " << std::abs(-5) << std::endl;  // 绝对值：5

  // <cstring> 内存操作
  int buffer[5];
  std::memset(buffer, 0, sizeof(buffer)); // 将整块内存快速初始化为 0（memset 属于全局空间也属于 std）
  std::cout << "Buffer[0] after memset: " << buffer[0] << std::endl;

  return 0;
}