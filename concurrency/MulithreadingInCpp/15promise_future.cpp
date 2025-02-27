#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>

using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

ull OddSum = 0;

// 奇数
void findOdd(std::promise<ull> &OddSumPromise, ull start, ull end)
{
  for (ull i = start; i <= end; ++i)
  {
    if ((i & 1) == 1)
    {
      OddSum += i;
    }
  }
  // 把值放到promise中，后续通过promise.get_future().get()得到值
  OddSumPromise.set_value(OddSum);
}

// 奇数
void findOdd1(std::promise<ull> &&OddSumPromise, ull start, ull end)
{
  for (ull i = start; i <= end; ++i)
  {
    if ((i & 1) == 1)
    {
      OddSum += i;
    }
  }
  // 把值放到promise中，后续通过promise.get_future().get()得到值

  // 注意，当std::thread按值传参时，此处修改的是std::thread中
  // 保存的参数副本，而不是main中的w。
  // 而当向std::thread按std::ref传参时，先会创建一个std::ref临时对象，
  // 其中保存着main中w引用。然后这个std::ref再以副本的形式保存在
  // std::thread中。随后这个副本被move到线程函数，由于std::ref重载了
  // operator T&(),因此会隐式转换为Widget&类型（main中的w），因此起到
  // 的效果就好象main中的w直接被按引用传递到线程函数中来。
  OddSumPromise.set_value(OddSum);
}

int main()
{
  ull start = 0, end = 1000000000;

  std::promise<ull> OddSum;
  std::future<ull> OddFuture = OddSum.get_future();
  cout << "Thread Created!" << endl;
  //引用传参
  std::thread t1(findOdd, std::ref(OddSum), start, end);

  // 因为这里使用了move，所以必须提前getFuture  右值传参
  // std::promise<ull> OddSum;
  // std::future<ull> OddFuture = OddSum.get_future();
  // cout << "Thread Created!" << endl;
  // std::thread t1(findOdd1, std::move(OddSum), start, end);

  cout << "Waiting for result!" << endl;
  auto value = OddFuture.get(); // 这里会阻塞
  cout << "odd sum: " << value << endl;

  cout << "Completed!" << endl;

  t1.join();

  return 0;
}