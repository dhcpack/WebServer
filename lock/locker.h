//
// Created by ylhappy on 2023/4/25.
//

#ifndef WEBSERVER_LOCKER_H
#define WEBSERVER_LOCKER_H

/*
线程同步：
  1. 信号量
  2. 互斥锁
  3. 条件变量

 RAII封装
 C++11 Style : https://blog.csdn.net/mingyuan_liu/article/details/115588505
 互斥锁：std::mutex
        lock_guard<_Mutex> RAII
        unique_guard<_Mutex> RAII

 条件变量：std::condition_variable
 */

#include <mutex>
#include <condition_variable>
#include <exception>
#include <semaphore.h>

/*
 * 信号量 Semaphore
 * PV操作
 * */
class Sem {
public:
    explicit Sem(int num = 0);

    ~Sem();

    bool wait();

    bool post();

private:
    sem_t sem_{};

    Sem(const Sem &);

    Sem operator=(const Sem &);
};


#endif // WEBSERVER_LOCKER_H
