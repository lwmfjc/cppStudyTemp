//#include <memory>
//#include <iostream>
//
//struct B; // 前置声明
//
//struct A {
//    A()
//    {
//        std::cout << "堆内存a1 创建了~" << std::endl;
//    }
//    std::shared_ptr<B> ptrB;
//    ~A() { std::cout << "堆内存a1 销毁了\n"; }
//};
//
//struct B {
//    B()
//    {
//        std::cout << "堆内存b1 创建了~" << std::endl;
//    }
//    //std::shared_ptr<A> ptrA;
//    std::weak_ptr<A> ptrA;
//
//    ~B() { std::cout << "堆内存b1 销毁了\n"; }
//};
//
//void test() {
//    std::cout << "---1" << std::endl;
//    auto a = std::make_shared<A>();//假设引用了堆内存a1
//    std::cout << "---2" << std::endl;
//    auto b = std::make_shared<B>();//假设引用了堆内存b1
//    a->ptrB = b; // a.ptrB 又引用 b1
//    b->ptrA = a; // b.ptrA 又引用 a1
//
//    //打印目前引用计数
//    std::cout << "a1被引用次数:" << a.use_count() << std::endl;
//    std::cout << "a1被引用次数:" << b->ptrA.use_count() << std::endl;
//    std::cout << "b1被引用次数:" << b.use_count() << std::endl;
//    std::cout << "b1被引用次数:" << a->ptrB.use_count() << std::endl;
//
//} 
////如果struct B的成员ptrA为share_ptr，则：函数结束，a 和 b 本该被销毁，但由于互相引用，a，b的析构函数执行了，但是a1，b1的析构函数永远不会执行！因为有多个引用指向a1，b1
//
//int main()
//{
//    test();
//    //这里结束后 栈内存a，b都销毁了
//    std::cout << "函数调用结束" << std::endl;
//    std::cin.get();
//    return 0;
//}
///*
//---1
//堆内存a1 创建了~
//---2
//堆内存b1 创建了~
//a1被引用次数:1
//a1被引用次数:1
//b1被引用次数:2
//b1被引用次数:2
//堆内存a1 销毁了
//堆内存b1 销毁了
//函数调用结束
//*/