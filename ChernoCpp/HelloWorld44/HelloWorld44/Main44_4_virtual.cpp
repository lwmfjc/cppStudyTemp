//#include <iostream>
//#include <cstring>
//
//class Entity {
//public:
//    virtual void SayName() { std::cout << "I am Entity" << std::endl; }
//};
//
//class Player : public Entity {
//public:
//    void SayName() override { std::cout << "I am Player" << std::endl; }
//};
//
//void Print(Entity* e) {
//    e->SayName(); // 强制程序通过虚表查找
//}
//
//int main() {
//    Entity base;
//    Player p1;
//
//    std::cout << "Before memcpy: ";
//    Print(&p1); // 应该输出 I am Player
//
//    // 暴力覆盖！把 base 的内存（包含 Entity 的 vptr）强行塞进 p1
//    std::memcpy(&p1, &base, sizeof(Entity));
//
//    std::cout << "After memcpy:  ";
//    Print(&p1); // 这次，它一定会输出 I am Entity！
//
//    std::cin.get();
//}