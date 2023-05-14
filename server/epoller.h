//
// Created by ylhappy on 2023/5/12.
//

#ifndef WEBSERVER_EPOLLER_H
#define WEBSERVER_EPOLLER_H

#include <sys/epoll.h> //epoll_ctl()
#include <fcntl.h>  // fcntl()
#include <unistd.h> // close()
#include <cassert> // close()
#include <vector>
#include <cerrno>

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
    int epollFd_;

    std::vector<struct epoll_event> events_;
};

#endif //WEBSERVER_EPOLLER_H
