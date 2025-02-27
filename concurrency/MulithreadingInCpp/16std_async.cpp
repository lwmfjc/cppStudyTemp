#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

using namespace std;
using namespace std::chrono;
typedef long int ull;

// 奇数
ull findOdd(ull start, ull end)
{
  cout << "[fundOdd()]start-----" << endl;
  cout << "[fundOdd()]ThreadId: " << std::this_thread::get_id() << '\n';
  ull OddSum = 0;
  for (ull i = start; i <= end; ++i)
  {
    if ((i & 1) == 1)
    {
      OddSum += i;
    }
  }
  cout << "[fundOdd()]end-----" << endl;
  return OddSum;
}

int main()
{

  cout << "[main]ThreadId: " << std::this_thread::get_id() << '\n';
  ull start = 0, end = 1000000000;

  cout << "Thread created if policy is std::launch::async!!\n";

  //std::launch::deferred-->直到调用OddSum.get()的时候才执行线程
  //deferred不会创建新线程
  std::future<ull> OddSum = std::async(std::launch::deferred, findOdd, start, end);

  //std::launch::async-->立即执行线程
  // std::future<ull> OddSum = std::async(std::launch::async, findOdd, start, end);

  // std::this_thread::sleep_for(std::chrono::seconds(3));

  cout << "Waiting For Result!" << endl;
  //等待线程的执行结果
  auto value = OddSum.get();
 
  cout << "odd sum: " << value << endl;

  cout << "Completed!" << endl;

  return 0;
}