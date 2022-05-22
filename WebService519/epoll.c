#include "Epoll.h"
#include "Util.h"
#include "base/Liggin.h"

#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define EVENTSNUM 4096
#define EPOLLWAITTIME 10000

// typedef shard_ptr<Channel> SP_Channel;

Epoll::Epoll() :epollFd_(epoll_create(EPOLL_CLOEXEC)), events_(EVENTSNUM) {
	assert(epollFd > 0);
}

Epoll::~Epoll() { }

// 注册新描述符
void Epoll::epollAdd(SP_Channel req, int timeOut) {
	int fd = req->getFd();
	if (timeOut > 0) {
		addTimer(req, timeOut);
		fd2chan_[fd] = req;
	}
	struct epoll_event event;
	event.data.fd = fd;
	event.enents = req->getEvents();

	request->equalAndUpdateLastEvents();

	fd2chan_[fd] = req;
	if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event) < 0) {
		perror("epoll_add error");
		fd2chan_[fd].reset();
	}
}

// 修改描述符状态
void Epoll::epollMod(SPChannel req, int timeOut) {
	if (timeOut > 0) {
		add_timer(req, timeOut);
	}
	int fd = req->getfd();
	if (!req->equalAndUpdateLastEvents()) {
		struct epoll_event event;
		event.data.fd = fd;
		event.events = rea->getEvents();
		if (epoll_ctl(epollFd, EPOLL_EVENT_MOD, fd, &event) < 0) {
			perror("epoll_mod error");
			fd2Chan_[fd].reset();
		
		}
	}
}

// 从epoll中删除描述符
void Epoll::epollDel(SPChannel req, it timeOut) {
	int fd = req->getfd();
	struct epoll_event event;
	event.data.fd = fd;
	event.events = rea->getLastEvents();
	if (epoll_ctl(epollFd, EPOLL_EVENT_DEL, fd, &event) < 0) {
		perror("epoll_del error");
	}
	fd2Chan_[fd].reset();
	fd2Http_[fd].reset();
}

// 返回活跃事件数
vector<SP_Channel> Epoll::getLivePoll() {
	while (true) {
		int eventCount = epoll_wait(epollFd_, &*events.begin(), events.size(), EPOLLWAIT_TIME);
		if (eventCount < 0) {
			perror("epoll wait error");
		} 
		vector<SP_Channel> req_data = getEventsRequest(event_count);
		if (req_data.size() > 0) {
			return req_data;
		}
	}
}

void Epoll::handleExpired() {
	timeManager_.handleExpiredEvent();
}

// 分发处理函数
vector<SP_Channel> Epoll::getEventsRequest(int eventsNum) {
	vector<SP_Channel> req_data;
	for (in i = 0; i < eventsNum; i++) {
		int fd = events_[i].data.fd;
		SP_Channel cur_req = fd2chan_[fd];
		if (cur_req) {
			cur_req->setRevents(events_[i].events);
			cur_req->setEvents(0);
			req_data.push_back(cur_req);
		} else {
			LOG << "sp cur_req invalid";
		}
	}
	return req_data;
}

void Epoll::addTumer(shared_ptr<Channel> reqData, int timeOut) {
	shared_ptr<HttpData> t = reqData->getHolder();
	if (t) {
		timeManager_.addTimer(t, timeOut);
	} else {
		LOG << "timer add fail";
	}
}








