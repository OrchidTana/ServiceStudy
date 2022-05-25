#pragma once

#include "Channel.h"
#include <pthread.h>
#include <functional>
#include <memory>
#include <vector>

#define THREADPOOL_INVALID -1
#define THREADPOOL_LOCK_FAILURE -2
#define THREADPOOL_QUEUE_FULL -3
#define THREADPOOL_SHUTDOWN -4
#define THREADPOOL_THREAD_FAILURE -5
#define THREADPOOL_GRACEFUL 1

#define MAX_THREADS 1024
#define MAX_QUEUE 65535

typedef enum {
	immediate_shutdown = 1,
	graceful_shutdown = 2
} shutDownOption;

struct ThreadPoolTask {
	std::function<void(std::shared_ptr<void>)> fun;
	shared_ptr<void> args;
};

class ThreadPool {

	public:
		static int threadPoolCreate(int thread_count, int queue_size);
		static int threadPoolAdd(std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> func);
		static int threadPoolDestroy(shutDownOption option = graceful_shutdown);
		static int threadPoolFree();
		static void* threadPoolThread(void* args);

	private:
		static pthread_mutex_t lock_;
		static pthread_cond_t notify_;

		static std::vector<pthread_t> threads_;
		static std::vector<ThreadPoolTask> queue_;
	
		static int threadCount_;
		static int queueSize_;
		static int head_;
		static int tail_;
		static int count_;
		static int shutDown_;
		static int started_;
}

