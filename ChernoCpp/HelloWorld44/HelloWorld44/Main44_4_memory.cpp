//#include <iostream>
//#include <cstring>
//
//struct BaseA {
//    int a = 111;
//};
//
//struct BaseB {
//    int b = 222;
//};
//
//// Child 同时拥有 a 和 b，继承顺序决定内存顺序，这里先BaseA-->BaseB-->自己的成员
////在内存里，Child 对象是一块连续的砖，布局如下（假设每个 int 占 4 字节）：
//// 字节偏移  内容  属于谁
//// 0    int a(111)  BaseA的地盘
//// 4    int b(222)  BaseB的地盘8int c(3)Child 的地盘
//struct Child : public BaseA, public BaseB {
//    int c = 333;
//};
//
//int main() {
//    Child p;
//    BaseB sourceB;
//    sourceB.b = 999; // 我们准备了一个新的 B，想把它拷进 p 里
//
//    std::cout << "--- 拷贝前 ---" << std::endl;
//    std::cout << "p.a = " << p.a << " (BaseA部分)" << std::endl;
//    std::cout << "p.b = " << p.b << " (BaseB部分)" << std::endl;
//
//    // --- 致命操作 ---
//    // 程序员的意图：把 sourceB 的数据拷贝给 p
//    // 程序员认为：p 既然继承了 BaseB，那我就直接拷过去
//    std::memcpy(&p, &sourceB, sizeof(BaseB));
//
//    std::cout << "\n--- 运行 memcpy(&p, &sourceB, ...) 后 ---" << std::endl;
//
//    // 错位发生了！
//    // 1. p.a 被改成了 999。因为 memcpy 从 p 的开头（BaseA的位置）开始写。
//    // 2. p.b 依然是 222。因为它在内存后面，memcpy 根本没写到它。
//
//    std::cout << "p.a = " << p.a << " (被错误覆盖了！)" << std::endl;
//    std::cout << "p.b = " << p.b << " (完全没被拷进去！)" << std::endl;
//
//    std::cin.get();
//
//    return 0;
//}