#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loopFor)
{
  if (loopFor < 0)
    return;
  //一个线程获取锁之后，另一个线程就不能再获取锁了
  //但是同一个线程可以多次获取锁
  m1.lock();
  m1.lock(); 
  cout << c << " " << buffer++ << endl;
  recursion(c, --loopFor);
  m1.unlock();
  m1.unlock(); 
  cout << "Unlocked By ThreadId" << c << endl; 
}

int main(){
  // thread t0(recursion,'0',10);
  // thread t1(recursion,'1',20);

  // t0.join();
  // t1.join();

  m1.lock();
  cout << "locked by main()-1" << endl;
  //允许多次lock()，因为这也是在同一个线程中(main线程)
  m1.lock();
  cout << "locked by main()-2" << endl;
  m1.lock();
  cout << "locked by main()-3" << endl;

  
  m1.unlock();
  cout << "unlocked by main()-3" << endl;
  m1.unlock();
  cout << "unlocked by main()-2" << endl;
  m1.unlock();
  cout << "unlocked by main()-1" << endl;


  return 0;
}