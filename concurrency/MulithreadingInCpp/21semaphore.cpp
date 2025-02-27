#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>

std::binary_semaphore smphSignalMainToThread{0},
    smphsignalThreadToMain{0};
void ThreadProc()
{
  // 等待主线程给它信号量,目前是0 无法获取
  smphSignalMainToThread.acquire();
  std::cout << "[thread] Got the signal\n";

  using namespace std::literals;
  // std::this_thread::sleep_for(std::chrono::milliseconds(300));
  std::this_thread::sleep_for(3s);
  std::cout << "[thread] Send the signal\n";
  smphsignalThreadToMain.release();
}
int main(){
  std::thread thrWorker(ThreadProc);

  std::cout << "[main] send signal\n";

  smphSignalMainToThread.release();

  smphsignalThreadToMain.acquire();

  std::cout << "[main] Got signal \n";
  thrWorker.join();

  
  return 0;
}