#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>
#include <deque>

using namespace std;

std::mutex mu;
std::condition_variable cond;
deque<int> buffer;

const unsigned int maxBufferSize = 50;

void producer(int val)
{
  // 最满50个，最多总生产100个
  while (val)
  {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, []()
              { return buffer.size() < maxBufferSize; });
    buffer.push_back(val);
    cout << "produced: " << val << endl;
    val--;
    locker.unlock();
    cond.notify_one();
  }
}

void consumer()
{
  while (true)
  {
    std::unique_lock<std::mutex> locker(mu);
    cond.wait(locker, []()
              { return buffer.size() > 0; });
    int val = buffer.back();
    buffer.pop_back();
    cout << "Consumed: " << val << endl;
    val--;
    locker.unlock();
    // 消费完之后通知其他线程(唤醒wait())
    // 可能是继续消费，也可能是生产
    cond.notify_one();
  }
}

int main()
{
  std::thread t1(producer, 100);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  std::thread t2(consumer);

  t1.join();
  t2.join();

  return 0;
}