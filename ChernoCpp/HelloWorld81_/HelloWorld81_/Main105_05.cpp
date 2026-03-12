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
    std::shared_ptr<A> ptrA;
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
        * 堆内存 b 里的成员变量 ptrA [sharedB.ptrA]（强引用 +1）
        * 总计计数：2
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


/*
    当函数执行到 } 时，栈帧销毁，局部变量 sharedA 和 sharedB 被释放。
    * 变量 sharedA 销毁：它原本指向 a，现在它没了，a 的引用计数从 2 降到了 1。
        * 注意：因为计数还没到 0，a 不会调用析构函数。
    * 变量 sharedB 销毁：它原本指向 b，现在它也没了，b 的引用计数从 2 降到了 1。
        * 注意：因为计数还没到 0，b 不会调用析构函数。
*/

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
a被引用次数:2
a被引用次数:2
b被引用次数:2
b被引用次数:2
*/
#endif