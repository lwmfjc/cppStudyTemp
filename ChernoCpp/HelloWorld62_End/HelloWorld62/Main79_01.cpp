#ifdef LY_EP79_

#include <iostream> 
#include <thread>
#include <chrono>
#include <future> 

static std::mutex mtx;
static std::vector<int> meshes;

static void LoadMesh(int i)
{
	std::cout << "Loading mesh...[" << i << "]\n";

	//加锁->互斥锁
	//该锁在当前作用域结束时自动释放 
	std::lock_guard<std::mutex> lock(mtx);

	//模拟：将加载的网格ID添加到共享资源中
	meshes.push_back(i);
	std::cout << "Mesh Added: " << i << "\n";


}

void LoadMeshes()
{
	//因为这里的异步任务，即LoadMesh函数返回void，所以我们使用std::future<void>来存储这些异步任务的结果。
	std::vector<std::future<void>> futures;

	for (int i = 10; i < 15; i++)
	{
		// std::async 确实启动了一个新线程。
		//1. 但是，因为它返回的 std::future 没有赋值给任何变量，它会在这一行结束时立刻析构。
		//2. std::future 的析构函数逻辑是：“等一下！任务还没跑完，我不能死，我要阻塞主线程直到子线程结束。”
		//3. 所以，最终导致主线程在每次调用 std::async 后都被阻塞，等待子线程完成，才继续下一次循环。
		//std::async(std::launch::async, LoadMesh, i);

		// 将 future 存入 vector，防止它立即析构
		//在单独线程中加载网格
		futures.push_back(std::async(std::launch::async, LoadMesh, i));
	}


}


void LoadMeshesSync()
{
	for (int i = 10; i < 15; i++)
	{
		LoadMesh(i);
	}


}

int main()
{
#define ASYNC 1
#if ASYNC 
	LoadMeshes();
#else
	LoadMeshesSync();
#endif
	std::cin.get();
	return 0;
}
/* Mesh Added:顺序是随机的，因为可能某线程执行std::lock_guard<std::mutex> lock(mtx);这行代码前，被其他线程抢先
Loading mesh...[10Loading mesh...[11]
]
Loading mesh...[12]
Loading mesh...[13]
Loading mesh...[14]
Mesh Added: 11
Mesh Added: 10
Mesh Added: 12
Mesh Added: 13
Mesh Added: 14
*/
#endif