#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool {
public:
	explicit ThreadPool(int numThreads);
	~ThreadPool();

	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args) 
		-> std::future<typename std::result_of<F(Args...)>::type>;

private:
	template <class F, class ...Args>
	struct Task {
		template<class G, class... A>
		Task(G&& g, A&&... a) 
			: function(std::bind(std::forward<G>(g), std::forward<A>(a)...)), 
			  future(promise.get_future()) 
		{ }

		std::function<typename std::result_of<F(Args...)>::type()> function;
		std::promise<typename std::result_of<F(Args...)>::type> promise;
		std::future<typename std::result_of<F(Args...)>::type> future;
	};

	void workerThread();
	std::vector<std::thread> threads;
    std::queue<std::function<void()>> taskQueue;  // Use a queue of functions
	std::mutex queueMutex;
	std::condition_variable condition;
	bool stop;
};

template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    auto task = std::make_shared<Task<F, Args...>>(std::forward<F>(f), std::forward<Args>(args)...);

    auto wrapped_task = [task] {
        task->promise.set_value(task->function());
    };

    {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push(wrapped_task);
    }
    condition.notify_one();
    return std::move(task->future); // Use std::move
}

#endif
