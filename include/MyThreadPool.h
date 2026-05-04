#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <type_traits>
#include <stdexcept>
 
class MyThreadPool
{
private:
	std::vector<std::thread> workers;
	std::queue < std::function<void()>> tasks;

	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;

public:
	MyThreadPool(size_t threads) :stop(false) {
		workers.reserve(threads);

		for (size_t i = 0; i < threads; ++i) {
			workers.emplace_back([this] {
				for (;;) {
					std::unique_lock<std::mutex> lock(queue_mutex);
					condition.wait(lock, [this] {
						return !tasks.empty() || stop;
						});
					if (tasks.empty() && stop) return;
					std::function<void()> currTask = std::move(tasks.front());
					tasks.pop();
					lock.unlock();
					currTask();
				}
				});
		}
	}

	~MyThreadPool() {
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop = true;
		lock.unlock();
		condition.notify_all();
		for (size_t i = 0; i < workers.size(); ++i) {
			workers[i].join();
		}
	}


	template<class F,class... Args>
	auto enqueue(F&& f, Args&&... args)
		-> std::future<typename std::invoke_result<F, Args...>::type> 
	{
		using return_type = typename std::invoke_result<F, Args...>::type;
		auto task = std::make_shared<std::packaged_task<return_type()>>(
			[f = std::forward<F>(f), ...args = std::forward<Args>(args)]() mutable {
				return std::invoke(f, args...);
			}
		);

		std::future<return_type> res = task->get_future();

		if (stop) throw std::runtime_error("Thread pool has stopped");

		std::unique_lock<std::mutex> lock(queue_mutex);
		tasks.push([this,task] {
			(*task)();
			});

		condition.notify_one();

		return res;
	}
};
