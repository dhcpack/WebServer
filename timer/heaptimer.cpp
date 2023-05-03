//
// Created by ylhappy on 2023/5/3.
//

#include "heaptimer.h"

HeapTimer::HeapTimer(size_t heap_size) {
    heap_.reserve(heap_size);
}

HeapTimer::~HeapTimer() {
    id2heap_.clear();
    heap_.clear();
}

void HeapTimer::swapNode(size_t i, size_t j) {
    std::swap(heap_[i], heap_[j]);
    id2heap_[heap_[i].id] = i;
    id2heap_[heap_[j].id] = j;
}

void HeapTimer::shiftup_(size_t node) {
    size_t fa = (node - 1) / 2;
    while (node != 0) {
        if (heap_[fa] < heap_[node]) break;
        swapNode(node, fa);
        node = fa;
        fa = (node - 1) / 2;
    }
}

void HeapTimer::shiftdown_(size_t node) {
    size_t child = node * 2 + 1, sz = heap_.size();
    while (child < sz) {
        if (child + 1 < sz && heap_[child + 1] < heap_[child]) child++;
        if (heap_[node] < heap_[child]) break;
        swapNode(node, child);
        node = child;
        child = node * 2 + 1;
    }
}

void HeapTimer::push(u_int id, time_t timeout, const TimeoutCallBack &cb) {
    size_t index;
    if (id2heap_.count(id) == 0) {  // 新节点，插入到堆尾
        index = heap_.size();
        id2heap_[id] = index;
        heap_.push_back({id, Clock::now() + MS(timeout), cb});
        shiftup_(index);
    } else {  // 已有节点，更新时间，调整位置
        index = id2heap_[id];
        heap_[index].expires = Clock::now() + MS(timeout);
        heap_[index].cb = cb;
        shiftdown_(id2heap_[id]);
        shiftup_(id2heap_[id]);
    }
}

// 删除指定id结点，并触发回调函数
void HeapTimer::doWork(u_int id) {
    if (id2heap_.count(id) == 0) {
        return;
    }
    size_t index = id2heap_[id];
    TimerNode node = heap_[index];
    node.cb();  // 回调函数
    del_(index);
}

// 删除指定位置的节点
void HeapTimer::del_(size_t index) {
    id2heap_.erase(heap_[index].id);

    if (index < heap_.size()) {  // 不是堆尾，交换到堆尾，删除并调整
        swapNode(index, heap_.size() - 1);
        heap_.pop_back();
        shiftdown_(index);
    } else {  // 是堆尾，直接删除
        heap_.pop_back();
    }
}

// 调整指定id的节点
void HeapTimer::refresh(u_int id, time_t newExpires) {
    assert(id2heap_.count(id) != 0);

    heap_[id2heap_[id]].expires = Clock::now() + MS(newExpires);;
    shiftdown_(id2heap_[id]);
}

// 清除超时节点
void HeapTimer::tick() {
    /* 清除超时结点 */
    if (heap_.empty()) {
        return;
    }
    while (!heap_.empty()) {
        TimerNode node = heap_.front();
        if (std::chrono::duration_cast<MS>(node.expires - Clock::now()).count() > 0) {
            break;
        }
        node.cb();
        pop();
    }
}

void HeapTimer::pop() {
    del_(0);
}

// 以堆中最小的时间间隔作为下一次的时间间隔
time_t HeapTimer::getNextTick() {
    tick();
    time_t res = 0;
    if (!heap_.empty()) {
        res = std::max(std::chrono::duration_cast<MS>(heap_.front().expires - Clock::now()).count(), 0L);
    }
    return res;
}