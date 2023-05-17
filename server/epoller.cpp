//
// Created by ylhappy on 2023/5/12.
//

#include "epoller.h"

Epoller::Epoller(int maxEvent):epollFd_(epoll_create(512)), events_(maxEvent){
    assert(epollFd_ >= 0 && events_.size() > 0);
}

Epoller::~Epoller() {
    close(epollFd_);
}

// EPOLL_CTL_ADD：将文件描述符 fd 添加到 epoll 实例中进行监听。
bool Epoller::addFd(int fd, uint32_t events) {
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;     // 事件描述符
    ev.events = events;  // 事件类型
    return 0 == epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &ev);
}

// EPOLL_CTL_MOD：修改已经添加到 epoll 实例中的文件描述符 fd 的监听事件。
bool Epoller::modFd(int fd, uint32_t events) {
    if(fd < 0) return false;
    epoll_event ev = {0};
    ev.data.fd = fd;
    ev.events = events;
    return 0 == epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &ev);
}

// EPOLL_CTL_DEL：从 epoll 实例中删除文件描述符 fd。
bool Epoller::delFd(int fd) {
    if(fd < 0) return false;
    epoll_event ev = {0};
    return 0 == epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, &ev);
}

// 等待事件的发生，并返回发生事件的数量，最大等待时间是timeoutMs
int Epoller::wait(int timeoutMs) {
    return epoll_wait(epollFd_, &events_[0], static_cast<int>(events_.size()), timeoutMs);
}

int Epoller::getEventFd(size_t i) const {
    assert(i < events_.size() && i >= 0);
    return events_[i].data.fd;
}

uint32_t Epoller::getEvents(size_t i) const {
    assert(i < events_.size() && i >= 0);
    return events_[i].events;
}