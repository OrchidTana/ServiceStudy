#ifndef THREAD_POOL_C11__
#define THREAD_POOL_C11__

#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>
#include<condition_variable>
#include<functional>
#include<future>
#include<queue>
#include<type_traits>
#include<utility>
#include<vector>



namespace pool {


	class ThreadGuard {

		public:

			ThreadGuard(std::vector<std::thread> &v) : threads_(v) { }

		private:

			ThreadGuard(ThreadGuard&& tg) = delete; // copy construst
			ThreadGuard& operator=(ThreadGuard&& td) = delete; // copy fuzhi
			ThreadGuard(const ThreadGuard& td) = delete;
			ThreadGuard& operator=(const ThreadGuard& tg) = delete;

			std::vector<std::thread>& threads_;

	};

	class ThreadPool {

		public:

			typedef std::function<void()> task_type;

			explicit ThreadPool(int n = 1) : stop_(false), tg_(threads_)  {
				int nthreads = n;
				if (nthreads <= 0) {
					nthreads = std::thread::hardware_concurrency();  // 获取硬件支持的并发线程数
					nthreads = nthreads == 0 ? 2 : nthreads;
				}

				for (int i = 0; i < nthreads; i++) {
					threads_.push_back(std::thread([this] {
					while (!stop_.load(std::memory_order_acquire)) {
						task_type task;
						{
							std::unique_lock<std::mutex> ulk(this->mtx_);
							this->cond_.wait(ulk, [this] {
									return stop_.load(std::memory_order_acquire) || !this->tasks_.empty();
							});

							if (stop_.load(std::memory_order_acquire)) {
								return;
							}

							task = std::move(this->tasks_.front());
							this->tasks_.pop();
						}
						task();
					}}));
				}
			}

			~ThreadPool() {
				stop();
				cond_.notify_all();
			}

			void stop() {
				stop_.store(true, std::memory_order_release);
			}

			template<typename Function, typename... args>
			std::function<typename std::result_of<Function(args...)>::type> add(Function&& fcn, args&&... arg) {

				typedef typename std::result_of<Function(args...)>::type return_type; 
				typedef std::packaged_task<return_type()> task;

				auto t = std::make_shared<task>(std::bind(std::forward<Function>(fcn), std::forward<args>(arg)...));		
				auto ret = t->get_future();

				{
					std::lock_guard<std::mutex> lg(mtx_);
					if (stop_.load(std::memory_order_acquire)) {
						throw std::runtime_error("thread pook has stoped");
					}
					tasks_emplace([t] {(*t)();});
				}

				cond_.notify_one();
				return ret;
			}


		private:
			ThreadPool(ThreadPool&&) = delete;
			ThreadPool& operator=(ThreadPool&&) = delete;
			ThreadPool(const ThreadPool&) = delete;
			ThreadPool& operator=(const ThreadPool&) = delete;

			std::atomic<bool> stop_;
			std::mutex mtx_;
			std::condition_variable cond_;

			std::queue<task_type> tasks_;
			std::vector<std::thread> threads_;
			pool::ThreadGuard tg_;

	};

};









#endif
