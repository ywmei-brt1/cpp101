#include "ThreadPool.h"

ThreadPool::ThreadPool(int numThreads) : stop(false) {
	for (int i = 0; i < numThreads; ++i) {
		threads.emplace_back(&ThreadPool::workerThread, this);
	}
}

ThreadPool::~ThreadPool() {
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		stop = true;
	}
	condition.notify_all();
	for (auto& thread : threads) {
		thread.join();
	}
}


void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return !taskQueue.empty() || stop; });
            if (stop && taskQueue.empty()) {
                break;
            }

            task = std::move(taskQueue.front());
            taskQueue.pop();
        }
        task();  // Execute the task
    }
}
