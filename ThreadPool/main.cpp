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

//ע�⣺
//1.Ϊ�̳߳��������֮ǰһ��Ҫ����setMaxQueueSize������������пɴ�ŵ����������
//2 ��������start�����̣߳����̳߳��˻�Ϊ���߳�