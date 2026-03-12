#ifdef LY_EP105_
#include <memory>
#include <iostream>

/* 以下
  * a 的引用计数：指向堆内存 a 的所有 shared_ptr 共同拥有的那个控制块里的强引用计数
  * b 的引用计数：指向堆内存 b 的所有 shared_ptr 共同拥有的那个控制块里的强引用计数
*/

struct B; // 前置声明

struct A {
    A()
    {
        std::cout << "堆内存a 创建了~" << std::endl;
    }
    std::shared_ptr<B> ptrB;
    ~A() { std::cout << "堆内存a 销毁了\n"; }
};

struct B {
    B()
    {
        std::cout << "堆内存b 创建了~" << std::endl;
    }
    std::weak_ptr<A> ptrA;
    ~B() { std::cout << "堆内存b 销毁了\n"; }
};

void test() {
    std::cout << "---1" << std::endl;
    auto sharedA = std::make_shared<A>();//假设引用了堆内存a
    std::cout << "---2" << std::endl;
    auto sharedB = std::make_shared<B>();//假设引用了堆内存b

    sharedA->ptrB = sharedB; // sharedA.ptrB 又引用了b
    sharedB->ptrA = sharedA; // sharedB.ptrA 又引用 a

    /*分析
    * 堆内存 a：被两个 shared_ptr 盯着：
        * 栈上的变量 sharedA（强引用 +1）
        * 堆内存 b 里的成员变量 ptrA [sharedB.ptrA]（弱引用 +1）
        * 总计计数：1
    * 堆内存 b：被两个 shared_ptr 盯着：
        * 栈上的变量 sharedB（强引用 +1）
        * 堆内存 a 里的成员变量 ptrB [sharedA.ptrB]（强引用 +1）
        * 总计计数：2

    */

    //打印目前引用计数
    std::cout << "a被引用次数:" << sharedA.use_count() << std::endl;
    std::cout << "a被引用次数:" << sharedB->ptrA.use_count() << std::endl;
    std::cout << "b被引用次数:" << sharedB.use_count() << std::endl;
    std::cout << "b被引用次数:" << sharedA->ptrB.use_count() << std::endl;

}

 

int main()
{
    test();
    std::cin.get();
    return 0;
}
/*
---1
堆内存a 创建了~
---2
堆内存b 创建了~
a被引用次数:1
a被引用次数:1
b被引用次数:2
b被引用次数:2
堆内存a 销毁了
堆内存b 销毁了
*/
#endif