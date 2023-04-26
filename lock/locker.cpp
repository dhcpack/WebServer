//
// Created by ylhappy on 2023/4/25.
//
#include "locker.h"

Sem::Sem(int num) {
    if (sem_init(&sem_, 0, num)) throw std::exception();
}

Sem::~Sem() {
    sem_destroy(&sem_);
}

bool Sem::wait() {
    return sem_wait(&sem_) == 0;
}

bool Sem::post() {
    return sem_post(&sem_) == 0;
}

