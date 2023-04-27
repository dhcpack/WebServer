//
// Created by ylhappy on 2023/4/25.
//

#ifndef WEBSERVER_BLOCKQUEUE_H
#define WEBSERVER_BLOCKQUEUE_H

/*
 * 线程安全的阻塞队列
 * RAII
 * 添加互斥锁
 * 使用条件变量实现生产者、消费者模式
 * */
#include <mutex>
#include <deque>
#include <condition_variable>

template<class Value_type>
class BlockQueue {
public:
    explicit BlockQueue(uint32_t MaxCapacity = 1024);

    ~BlockQueue();

    void clear();

    bool empty();

    bool full();

    void close();

    uint32_t size();

    uint32_t capacity();

    Value_type front();

    Value_type back();

    void push_front(const Value_type &item);

    void push_back(const Value_type &item);

    bool pop(Value_type &item);

    bool pop(Value_type &item, time_t timeout);

    void flush();

private:
    std::deque<Value_type> deque_;

    uint32_t capacity_;

    std::mutex mutex_;

    bool isClose_;

    std::condition_variable condConsumer_;

    std::condition_variable condProducer_;
};

template<class Value_type>
BlockQueue<Value_type>::BlockQueue(uint32_t capacity) : capacity_(capacity), isClose_(false) {}

template<class Value_type>
BlockQueue<Value_type>::~BlockQueue() {
    close();
}

template<class Value_type>
void BlockQueue<Value_type>::clear() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    deque_.clear();
}

template<class Value_type>
bool BlockQueue<Value_type>::empty() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    return deque_.empty();
}

template<class Value_type>
bool BlockQueue<Value_type>::full() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    return deque_.size() >= capacity_;
}

template<class Value_type>
void BlockQueue<Value_type>::close() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    deque_.clear();
    isClose_ = true;
    condProducer_.notify_all();
    condConsumer_.notify_all();
}

template<class Value_type>
uint32_t BlockQueue<Value_type>::size() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    return deque_.size();
}

template<class Value_type>
uint32_t BlockQueue<Value_type>::capacity() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    return capacity_;
}

template<class Value_type>
Value_type BlockQueue<Value_type>::front() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    return deque_.front();
}

template<class Value_type>
Value_type BlockQueue<Value_type>::back() {
    std::lock_guard<std::mutex> lockGuard(mutex_);
    return deque_.back();
}

template<class Value_type>
void BlockQueue<Value_type>::push_front(const Value_type &item) {
    std::unique_lock<std::mutex> uniqueLock(mutex_);
    while (deque_.size() >= capacity_) {
        condProducer_.wait(uniqueLock);
    }
    deque_.push_front(item);
    condConsumer_.notify_one();
}

template<class Value_type>
void BlockQueue<Value_type>::push_back(const Value_type &item) {
    std::unique_lock<std::mutex> uniqueLock(mutex_);
    while (deque_.size() >= capacity_) {
        condProducer_.wait(uniqueLock);
    }
    deque_.push_back(item);
    condConsumer_.notify_one();
}

template<class Value_type>
bool BlockQueue<Value_type>::pop(Value_type &item) {
    std::unique_lock<std::mutex> uniqueLock(mutex_);
    while (deque_.empty()) {   /*   avoid spurious wakeup    */
        condConsumer_.wait(uniqueLock);
        if (isClose_) return false;
    }
    item = deque_.front();
    deque_.pop_front();
    condProducer_.notify_one();
    return true;
}

template<class Value_type>
bool BlockQueue<Value_type>::pop(Value_type &item, time_t timeout) {
    std::unique_lock<std::mutex> uniqueLock(mutex_);
    while (deque_.empty()) {    /*   avoid spurious wakeup    */
        if (condConsumer_.wait_for(uniqueLock, std::chrono::seconds(timeout)) == std::cv_status::timeout) {
            return false;
        }
        if (isClose_) return false;
    }
    item = deque_.front();
    deque_.pop_front();
    condProducer_.notify_one();
    return true;
}

/*
 * 唤醒一个消费者
 * */
template<class Value_type>
void BlockQueue<Value_type>::flush() {
    condConsumer_.notify_one();
}


#endif //WEBSERVER_BLOCKQUEUE_H
