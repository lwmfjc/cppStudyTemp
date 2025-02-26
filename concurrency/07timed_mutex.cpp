#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
int myAmount = 0;
std::timed_mutex m;
void increment(int i)
{
  // if (m.try_lock_for(std::chrono::seconds(1)))
  auto now=std::chrono::steady_clock::now();
  //值为1,2时第二个线程都是进不去的
  if (m.try_lock_until(now + std::chrono::seconds(1)))
  {
    cout << "Thread " << i << "Entered" << endl;
    ++myAmount;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    m.unlock();
  }
  else
  {
    cout << "Thread " << i << " Couldn't Enter" << endl;
  }
}

void test(int i)
{
  cout << "[" << i << "]waiting for " << i << " seconds" << endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  cout << "[" << i << "]wait end." << endl;
}
int main()
{
  /* cout << "main start..." << endl;
  std::thread t3(test, 3);
  std::thread t2(test, 2);
  std::thread t1(test, 1);

  cout << "main t1.join()..." << endl;
  t1.join();
  cout << "main t2.join()..." << endl;
  t2.join();
  cout << "main t3.join()..." << endl;
  t3.join();
  cout << "main continue..." << endl; */

  std::thread t1(increment, 1);
  std::thread t2(increment, 2);

  t1.join();
  t2.join();

   cout << myAmount << endl;
}