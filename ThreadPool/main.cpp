#include <iostream> 
#include<windows.h>
#include "ThreadPool.h"  


using namespace std;


void Test(int i)
{
	printf("Hello world %d time\n", i);
	Sleep(500);
}

int main()
{
	xcyk::ThreadPool threadPool("xcyk");
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);
	DWORD theadnum = SystemInfo.dwNumberOfProcessors+2;
	threadPool.setMaxQueueSize(10);
	threadPool.start(theadnum);
	for (int i = 0; i < 50; ++i)
	{
		auto task = bind(Test, i);
		threadPool.run(task);
	}
	getchar();
	return 0;
}

//注意：
//1.为线程池添加任务之前一定要调用setMaxQueueSize，设置任务队列可存放的最大任务数
//2 若不调用start创建线程，则线程池退化为单线程