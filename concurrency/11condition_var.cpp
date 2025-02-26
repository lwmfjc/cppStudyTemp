#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int money)
{
  // std::lock_guard<mutex> lg(m);
  m.lock();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  // balance += money;
  cout << "[addMoney]Amount Added Current Balance: " << balance << endl;
  // 这里不会等待，通知完后继续下一条语句(notify并不会释放锁)
  cv.notify_one();
  cout << "[addMoney]====== addMoney(int) end ======= " << endl;
  m.unlock();
}

void withdrowMoney(int money)
{
  // 获取锁m
  std::unique_lock<mutex> ul(m, std::defer_lock);
  cout << "now is :" << (ul.owns_lock() ? "locked" : "unlocked") << endl;
  ul.lock();
  cout << "now is :" << (ul.owns_lock() ? "locked" : "unlocked") << endl;
  cout << "[withdrowMoney]获取到了锁---" << endl;

  // 这里用wait_for，

  // [情形1] 接到notify通知后主动尝试获取锁后再进行条件判断(如果没有获取到锁，则会一直等待),
  // 如果为false则释放锁并且等待通知，为true则持有锁继续执行

  // [情形2] 或者如果3s后没接到通知，主动尝试获取锁后再进行条件判断，
  // 如果获取锁失败，则会再继续等待3s，之后再尝试获取锁后再进行条件判断
  // 获取到了锁之后，不论条件判断结果如何，都会持有锁后并继续语句执行
  cv.wait_for(ul, std::chrono::seconds(3), []
              {
    // [wait, 不是wait_for]如果为false则释放锁并且等待通知，为true则持有锁并继续执行
    // 获取到锁之后才会再次进行该判断函数的执行
    bool pass = (balance != 0);
    if (!pass)
    {
      cout << "[withdrowMoney]释放锁并等待通知---" << endl;
    }
    else
    {
      cout << "[withdrowMoney]释放锁并继续往下执行---" << endl;
    }
    return pass; });
  if (balance >= money)
  {
    balance -= money;
    cout << "Amount Deducted: " << money << endl;
  }
  else
  {
    cout << "Amount Can't Be Deducted, Current Balance Is Less Than " << money << endl;
  }
  //判断目前是否上锁
  cout << "now is :" << (ul.owns_lock() ? "locked" : "unlocked") << endl;

  cout << "Current Balance Is: " << balance << endl;
}

int main()
{
  std::thread t1(withdrowMoney, 500);
  std::thread t2(addMoney, 500);
  t1.join();
  t2.join();

  return 0;
}