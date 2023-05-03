//
// Created by ylhappy on 2023/5/3.
//

#ifndef WEBSERVER_HEAPTIMER_H
#define WEBSERVER_HEAPTIMER_H

/*
 * 定时器，时间堆实现，vector模拟二叉堆
 * */
#include <queue>
#include <unordered_map>
#include <ctime>
#include <algorithm>
#include <arpa/inet.h>
#include <functional>
#include <cassert>
#include <chrono>
#include "../log/log.h"

typedef std::function<void()> TimeoutCallBack;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::milliseconds MS;
typedef Clock::time_point TimeStamp;

struct TimerNode {
    u_int id;
    TimeStamp expires;
    TimeoutCallBack cb;

    bool operator<(const TimerNode &t) const {
        return expires < t.expires;
    }
};

class HeapTimer {
public:
    explicit HeapTimer(size_t heap_size = 64);

    ~HeapTimer();

    void refresh(u_int id, time_t newExpires);

    void push(u_int id, time_t timeOut, const TimeoutCallBack &cb);

    void doWork(u_int id);

    void tick();

    void pop();

    time_t getNextTick();

private:
    void del_(size_t i);

    void shiftup_(size_t node);

    void shiftdown_(size_t node);

    void swapNode(size_t i, size_t j);

    std::vector<TimerNode> heap_;

    std::unordered_map<u_int, size_t> id2heap_;
};

#endif //WEBSERVER_HEAPTIMER_H
