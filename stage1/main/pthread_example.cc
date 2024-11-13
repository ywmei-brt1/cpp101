#include <iostream>
#include <pthread.h>
#include <unistd.h> // for sleep()
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

// Function to be executed by the thread
void* print_hello(void* arg) {
  int job_id = *(int*)arg;
  std::cout << "Thread " << pthread_self() << " processing job " << job_id << std::endl;
  sleep(1); // Simulate some work
  std::cout << "Thread " << pthread_self() << " finished job " << job_id << std::endl;
  return nullptr;
}

// Structure to hold job information
struct Job {
  int id;
};

// Thread pool class
class ThreadPool {
public:
  ThreadPool(int numThreads) : stop(false) {
    for (int i = 0; i < numThreads; ++i) {
      pthread_t thread;
      int result = pthread_create(&thread, nullptr, workerThread, this);
      if (result != 0) {
        std::cerr << "Error creating thread: " << result << std::endl;
        // Handle error (e.g., throw an exception)
      }
      threads.push_back(thread);
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(mutex);
      stop = true;
    }
    condition.notify_all();
    for (pthread_t thread : threads) {
      pthread_join(thread, nullptr);
    }
  }

  void enqueueJob(Job job) {
    {
      std::unique_lock<std::mutex> lock(mutex);
      jobQueue.push(job);
    }
    condition.notify_one();
  }

private:
  static void* workerThread(void* arg) {
    ThreadPool* pool = static_cast<ThreadPool*>(arg);
    while (true) {
      Job job;
      {
        std::unique_lock<std::mutex> lock(pool->mutex);
        pool->condition.wait(lock, [pool]{ return !pool->jobQueue.empty() || pool->stop; });
        if (pool->stop && pool->jobQueue.empty()) {
          break; // Exit thread
        }
        job = pool->jobQueue.front();
        pool->jobQueue.pop();
      }
      print_hello(&job.id);
    }
    return nullptr;
  }

  std::vector<pthread_t> threads;
  std::queue<Job> jobQueue;
  std::mutex mutex;
  std::condition_variable condition;
  bool stop;
};

int main() {
  // Create a thread pool with 3 threads
  ThreadPool threadPool(3);

  // Enqueue jobs 1 to 15
  for (int i = 1; i <= 15; ++i) {
    threadPool.enqueueJob({i});
  }

  // The thread pool's destructor will handle joining the threads

  std::cout << "Main thread exiting." << std::endl;
  return 0;
}