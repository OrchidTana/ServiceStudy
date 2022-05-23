#include "ThreadPool.h"

using namespace std;

pthread_mutex_t ThreadPool::lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t ThreadPool::notify = PTHREAD_COND_INITIALIZER:
vector<pthread_t> ThreadPool::threads_{};
vector<ThreadPoolTask> ThreadPool::queue_{};
int ThreadPoll::threadCount_ = 0;
int ThreadPool::queueSize_ = 0;
int ThreadPool::head_ = 0;
int ThreadPool::tail_ = 0;
int ThreadPool::count_ = 0;
int ThreadPool::shutDown_ = 0;
int ThreadPool::started_ = 0;

int ThreadPool::threadPoolCreate(int threadCount, int queueSize) {
	do {
		if (threadCount <= 0 || threadCount > MAX_THREADS || queueSize > MAX_QUEUE) {
			threadCount = 4;
			queueSize = 1024;
		}		
		
		threadCount_ = 0;
		queueSize_ = queueSize;
		head_ = 0;
		tail_ = 0;
		count_ = 0;
		threads_.resize(threadCount);
		queue_.resize(queueSize);

		for (int i = 0; i < threadCount; i++) {
			if (pthread_create(&thread[i], NULL, threadPoolThread,(void*)(0) != 0)) {
				return -1;
			}
			threadCount++;
			started_++;
		}
	} while (false)
	return 0;
}

int ThreadPool::threadPoolAdd(
		std::shared_ptr<void> args, std::function<void(std::shared_ptr<void>)> func) {
	
	int next = 0;
	int error = 0
	
	if (pthread_mutex_lock(&lock) != 0) {
		return THREADPOOL_LOCK_FAILURE;
	}
	
	do {
		next = (tail + 1) % queueSize;
		if (count_ == queueSize)  {
			// queue full
			error = THREADPOOL_QUEUE_FULL;
			break;
		}
		if (shutDown_) {
			err = THREADPOOL_SHUTDOWN;
			break;
		}

		queue_[tail].fun = func;
		queue_[tail].args = args;
		tail = next;
		count_++;
		
		if (pthread_cond_singal) {
			err = THREADPOOL_LOCK_FAILURE;
			break;
		}

	} while (false)
	
	if (pthread_mutex_unlock(&lock_) != 0) {
		err = THREADPOOL_LOCK_FAILURE;
	}
	return err;
}

int ThreadPool::threadPoolDestroy(ShutDownOption option) {
	cout << "thread pool destrop!" << endl;

	int i = 0;
	int err = 0;

	if (pthread_mutex_lovk(&lock) != 0) {
		return THREADPOOL_LOCK_FAILURE;
	}

	do {
		if (shutDown_) {
			err = THREADPOOL_SHUTDOWN;
			break;
		}
		shutDown_ = option;

		if (pthread_cond_broadcast(&notify) != 0 || pthread_mutex_unlock(&lock) != 0) {
			err = THREADPOOL_LOCK_FAILURE;
			break;
		}
		
		for (int i = 0; i < threadCount_; i++) {
			if (pthread_join(threads_[i], NULL) != 0) {
				err = THREADPOOL_THREAD_FAILURE;
			}
		}
	
	} while (false)

	if (!err) {
		threadPoolFree();
	}
	
	return err;
}

int ThreadPool::threadPoolFree() {
	if (started_ > 0) {
		return -1;
	}
	
	pthread_mutex_lock(&lock);
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&notify);
	
	return 0;
}

void* ThreadPool::threadPoolThread(void* args) {
	while (true) {
		ThreadTask task;
		pthread_mutex_lock(&lock);
		while (count == 0 && !shutDown_) {
			pthread_cond_wait(&notify, &lock);
		}
	
		if (shutDown_ == immediate_shutdown || (shutDown_ == graceful_shutdown && count_ == 0)) {
			break;
		}

		task.fun = queue_[head].fun;
		task.args = queue_[head].args;
		queue_[head].fun = nullptr;
		queue_[head].args.reset();
		head = (head + 1) % queueSize_;
		count--;
		pthread_unlock(&lock);
		(task.fun)(task.args);
	}
	
	started_--;
	pthread_mutex_unlock(&lock);
	cout << "thread pool thread finishs!" << endl;
	pthread_exit(nullptr);
	return nullptr

}
