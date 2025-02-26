#include <iostream>
#include <thread>
#include <mutex>
using namespace std;


std::mutex m1;
int buffer = 0;

void task(const char *threadNumber, int loopFor)
{
  //会自动上锁和解锁
  // std::unique_lock<mutex> lock(m1);
  // std::lock_guard<mutex> lock(m1);
  //不会自动上锁，需要显式上锁。但是会自动解锁。
  std::unique_lock<mutex> lock(m1,std::defer_lock);
  lock.lock();
  // m1.lock();
  for (int i = 0; i < loopFor; ++i)
  {
    buffer++;
    // cout << threadNumber  << "---" << buffer << endl;
  }
  // m1.unlock();
}

int main()
{
  thread t1(task, "T0", 10000);
  thread t2(task, "T1", 10000);

  t1.join();
  t2.join();

  cout << buffer << endl;
  return 0;
}