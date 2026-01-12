//#include <iostream>
//#include <memory>
//class Entity {};
//int main() {
//    // 1. 创建第一个 unique_ptr
//    std::unique_ptr<Entity> entity = std::make_unique<Entity>();
//
//    // 2. 使用 std::move 转移所有权
//    // 此时，entity 原有的内存所有权交给了 e2
//    std::unique_ptr<Entity> e2 = std::move(entity);
//
//    // 3. 检查状态
//    if (entity == nullptr) {
//        std::cout << "entity 现在是空的 (nullptr)" << std::endl;
//    }
//
//    if (e2 != nullptr) {
//        std::cout << "e2 现在拥有 Entity 的所有权" << std::endl;
//    }
//
//    std::cin.get();
//    return 0;
//} // e2 在这里离开作用域，Entity 被自动销毁