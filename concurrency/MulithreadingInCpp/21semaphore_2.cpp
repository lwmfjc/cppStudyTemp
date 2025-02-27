#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

std::binary_semaphore mysmphSignal1_2{0},mysmphSignal2_1{0};
void func1()
{
  int n = 0; // 0 -> ...
  while (n <= 100)
  {
    std::cout << "[func1]" << n++ << std::endl;
    mysmphSignal1_2.release();
    std::cout << "[func1]" << n++ << std::endl;
    mysmphSignal1_2.release();
    std::cout << "[func1]" << n++ << std::endl;
    mysmphSignal1_2.release();

    mysmphSignal2_1.acquire();
    // std::cout << "[func1]" << n++ << std::endl;
    // mysmphSignal.release();
    // std::cout << "[func1]" << n++ << std::endl;
    // mysmphSignal.release();
  }
}
void func2()
{
  int n = 100; // 100 -> ...
  while (n <= 200)
  {
    //获取到3个信号量才能继续执行
    
    mysmphSignal1_2.acquire();
    mysmphSignal1_2.acquire();
    mysmphSignal1_2.acquire();
    std::cout << "[func2]" << n++ << std::endl;
    std::cout << "[func2]" << n++ << std::endl;
    std::cout << "[func2]" << n++ << std::endl;
    mysmphSignal2_1.release();
    // std::cout << "[func2]" << n++ << std::endl;
    // mysmphSignal.acquire();
    // std::cout << "[func2]" << n++ << std::endl;
    // mysmphSignal.acquire();
  }
}

int main()
{
  std::thread thrWorker1(func1);
  std::thread thrWorker2(func2);

  thrWorker2.join();
  thrWorker1.join();

  return 0;
}