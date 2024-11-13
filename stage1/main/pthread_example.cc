#include <iostream>
#include <unistd.h> // for sleep()
#include "ThreadPool.h"

int my_task(int job_id) {
  std::cout << "Thread processing job " << job_id << std::endl;
  sleep(1); 
  std::cout << "Thread finished job " << job_id << std::endl;
  return job_id;
}


int main() {
  ThreadPool threadPool(3);

  std::vector<std::future<int>> results;
  for (int i = 1; i <= 15; ++i) {
	 results.emplace_back(threadPool.enqueue([i] { return my_task(i);}));
  }

	for(auto &result: results) {
		std::cout << "Result from thread: " << result.get() << std::endl;
	}

  std::cout << "Main thread exiting." << std::endl;
  return 0;
}
