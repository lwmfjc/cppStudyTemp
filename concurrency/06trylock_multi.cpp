// 只要任意一个锁获取失败就会返回数字（0,1,2,3...）
// std::try_lock(m0,m1,m2,m3,m4)
// 如果直到m3lock失败，则会释放m0,m1,m2

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

int X = 0, Y = 0;
std::mutex m1, m2;
void doSomeWorkForSeconds(int seconds)
{
  std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
void incrementsXY(int &XorY, std::mutex &m, const char *desc)
{
  for (int i = 0; i < 5; ++i)
  {
    m.lock();
    ++XorY;
    cout << desc << XorY << '\n';
    m.unlock();
    // 每次加完1之后都得等1秒钟
    doSomeWorkForSeconds(1);
  }
}
void consumeXY()
{
  int useCount = 5;
  int XplusY = 0;
  while (1)
  {
    // 死循环中同时获取两个锁
    // 期间不允许有人使用X或Y
    int lockResult = std::try_lock(m1, m2);
    if (lockResult == -1)
    {
      if (X != 0 && Y != 0)
      {
        --useCount;
        XplusY += X + Y;
        X = 0;
        Y = 0;
        cout << "XplusY" << XplusY << '\n';
      }
      m1.unlock();
      m2.unlock();
      // 次数用完后退出循环
      if (useCount == 0)
        break;
    }
  }
}

void test(int &x)
{
  cout << "mytest: " << x << std::endl;
}
int main()
{
  int myvalue{1};
  test(myvalue);
  std::thread t1(incrementsXY, std::ref(X), std::ref(m1), "X ");
  std::thread t2(incrementsXY, std::ref(Y), std::ref(m2), "Y ");
  std::thread t3(consumeXY);

  t1.join();
  t2.join();
  t3.join();
  return 0;
}