#pragma once

#include<thread>
#include<mutex>
#include<functional>
#include<string>
#include<condition_variable>
#include<deque>
#include<vector>
#include<memory>


namespace xcyk
{
	class ThreadPool
	{
	public:
		typedef std::function<void()> Task;

		explicit ThreadPool(const std::string &name = std::string());
		~ThreadPool();

		void start(int numThreads);//设置线程数，创建numThreads个线程
		void stop();//线程池结束
		void run(const Task& f);//任务f在线程池中运行
		void setMaxQueueSize(int maxSize);//设置任务队列可存放最大任务数

	private:
		bool isFull();//任务队列是否已满
		void runInThread();//线程池中每个thread执行的function
		Task take();//任务队列中取出一个任务

		std::mutex m_mutex;
		std::condition_variable m_notEmpty;
		std::condition_variable m_notFull;
		std::string m_name;
		std::vector<std::thread> m_threads;
		std::deque<Task> m_queue;
		size_t m_maxQueueSize;
		bool m_running;

		private:
		ThreadPool(const ThreadPool& x) = delete;//不能让其拷贝
		ThreadPool& operator=(const ThreadPool& x) = delete;
	};
}