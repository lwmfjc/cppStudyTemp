#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::condition_variable cv;
std::mutex m;
long balance = 0;

void func1()
{
  cout << std::this_thread::get_id() << "[func1]====== func1() start ======= " << endl;
  std::unique_lock<mutex> lg(m);

  cout << std::this_thread::get_id() << "[func1]等待5s后通知所有阻塞线程....." << endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));
  balance += 5;
  cv.notify_all();

  cout << std::this_thread::get_id() << "[func1]====== 5秒后锁释放 ======= " << endl;
  std::this_thread::sleep_for(std::chrono::seconds(5));

  cout << std::this_thread::get_id() << "[func1]====== func1() end ======= " << endl;
}

void func2()
{
  cout << std::this_thread::get_id() << "[func2]======  start ======= " << endl;
  std::unique_lock<mutex> lg(m);
  cout << std::this_thread::get_id() << "[func2]======  获取到了锁 ======= " << endl;

  /*
  　当其他线程用notify_one()将本线程wait()唤醒后，这个wait被唤醒后

　　1、wait()【【不断尝试获取互斥量锁】】，如果获取不到那么流程就卡在wait()这里等待获取，如果获取到了，那么wait()就继续执行，获取到了锁

　　2.1、如果wait有第二个参数就判断这个lambda表达式。

　　　　a)【【如果表达式为false，那wait又对互斥量解锁，然后又休眠，等待再次被notify_one()唤醒】】
　　　　b)如果lambda表达式为true，则wait返回，流程可以继续执行（此时互斥量已被锁住）。
　　2.2、如果wait没有第二个参数，则wait返回，流程走下去。
  */
  cv.wait(lg, []() -> bool
          {    
            bool pass = (balance != 0);
            if (!pass)
            {
              cout << std::this_thread::get_id() << "[func2]条件不成立,释放锁并等待通知---" << endl;
            }
            else
            {
              cout << std::this_thread::get_id() << "[func2]条件成立,持有锁并继续往下执行---" << endl;
            }
            return pass; });

  cout << std::this_thread::get_id() << "[func2]====== func2() end ======= " << endl;
} 

int main()
{
  std::thread t2(func2);
  std::thread t3(func2);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::thread t1(func1);
  t1.join();
  t2.join();
  t3.join();

  return 0;
}