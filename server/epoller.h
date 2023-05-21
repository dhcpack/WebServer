//
// Created by ylhappy on 2023/5/12.
//

#ifndef WEBSERVER_EPOLLER_H
#define WEBSERVER_EPOLLER_H

#include <sys/epoll.h> //epoll_ctl()
#include <unistd.h> // close()
#include <cassert> // close()
#include <vector>

class Epoller {
public:
    explicit Epoller(int maxEvent = 1024);

    ~Epoller();

    bool addFd(int fd, uint32_t events);

    bool modFd(int fd, uint32_t events);

    bool delFd(int fd);

    int wait(int timeoutMs = -1);

    int getEventFd(size_t i) const;

    uint32_t getEvents(size_t i) const;

private:
    // epoll文件描述符
    int epollFd_;
    // epoll事件
    std::vector<struct epoll_event> events_;
};

#endif //WEBSERVER_EPOLLER_H
