#include <iostream>
#include <thread>
#include <mutex>

int myAmount = 0;

std::mutex m;
void addMoney()
{
  for (int i = 0; i < 10000; i++)
    // if (m.try_lock())
    {
      m.lock();
      ++myAmount;
      m.unlock();
    }
}

int main()
{
  std::thread t1(addMoney);
  std::thread t2(addMoney);

  // 等待t1执行完毕
  t1.join();
  // 等待t2执行完毕
  t2.join();

  // 应该是20000
  std::cout << myAmount << std::endl;

  return 0;
}