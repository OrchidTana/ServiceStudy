#pragma once

#include <sys/epoll.h>
#include <memory>
#include <map>
#include <vector>
#include <assert.h>
#include <errno.h>
#include <netinet.h>
#include <string>
#include <sys/socket.h>
#include <queue>
#include <deque>
#include "Channel.h"
#include "HttpData.h"
#include "Timer.h"

#define MAXFD 100000

class Epoll {

 public:
	
	Epoll();
	~Epoll();

	void epollAdd(SPChannel req, int timeOut);
	void epollMod(SPChannel req, int timeOut);
	void epollDel(SPChannel req);
	void addTimer(std::shared_ptr<Channel> requestData, int timeOut);
	std::vector<std::shared_ptr<Channel>> getLivePool();
	std::vector<std::shared_ptr<Channel>> getEventsRequest(int eventsNum);
	int getEpollFd() { return epollFd_; }
	void handleExpired();

 private:
  
	int epollFd_;
	std::vector<epoll_event> events;
	std::shared_ptr<Channel> fd2chan_[MAXFD];
	std::shared_ptr<HttpData> fd2http_[MAXFD];
	TimerManager timerManager_;
};

