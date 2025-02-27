#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
void run(int count)
{
  while (count-- > 0)
    cout << "Cpp" << count << endl;

  std::this_thread::sleep_for(chrono::seconds(5));
  cout << "thread[" << std::this_thread::get_id() << "] finished" << endl;
}

void newThread()
{
  std::thread t2(run, 10);
  // 主线程结束后继续运行该线程(分离)
  t2.detach();
  cout << "thread[" << std::this_thread::get_id() << "] finished" << endl;
}

int main()
{
  std::thread t1(newThread);

  cout << "main()1" << endl;

  // waits for the thread to finish its execution
  // 等待线程完成执行
  /*   t1.join();//等待线程t1执行完毕
    // t1.join();//不允许两次join()，Error
    if(t1.joinable()){
      t1.join();
    } */

  /* Separates the thread of execution from the thread object, allowing execution to continue independently. Any allocated resources will be freed once the thread exits.
  将执行线程与线程对象分开，从而使执行能够独立继续。线程退出后，任何分配的资源都将被释放。 */
  // 执行后joinable is false.

  //  t1.detach();
  cout << "main()2" << endl;
  std::this_thread::sleep_for(chrono::seconds(20));
  /*
  main()1
  main()2
  thread[2] finished
  Cpp9
  Cpp8
  Cpp7
  Cpp6
  Cpp5
  Cpp4
  Cpp3
  Cpp2
  Cpp1
  Cpp0
  thread[3] finished  
  //这是因为析构函数中进行了判断
  If joinable() then terminate(), otherwise no effects. [ Note: Either implicitly detaching or joining a joinable() thread in its destructor could result in difficult to debug correctness (for detach) or performance (for join) bugs encountered only when an exception is raised. Thus the programmer must ensure that the destructor is never executed while the thread is still joinable. — end note ]

  What this means is that you should not let threads go out of scope without first calling either join() or detach().
这意味着您不应该在不首先调用join()或detach()情况下让线程脱离范围。

The way you describe it, you want the thread to go out of scope without joining so it will continue to run as your application runs. That requires a call to detach(). From there, I can only offer a little wisdom...
您的描述方式，希望线程不在范围内而无需加入，因此它将在您的应用程序运行时继续运行。这需要打电话以detach() 。从那里，我只能提供一些智慧...

That thread is now completely responsible for its own lifetime. If it doesn't return on its own, it will run forever (until the process terminates).
现在，该线程对自己的生命完全负责。如果它不自行返回，它将永远运行（直到过程终止）。

You are getting user input, presumably from something like cin or getch(). If these are accessed from multiple threads, you do not have much assurance that there are not race conditions in their library implementations. Tread lightly.
您正在获取用户输入，大概是从cin或getch()之类的内容中获得的。如果从多个线程访问这些内容，您就不会太多保证其图书馆实施中没有种族条件。轻轻踩踏。

  terminate called without an active exception
  */
  return 0;
}