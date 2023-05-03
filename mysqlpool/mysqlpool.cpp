//
// Created by ylhappy on 2023/5/3.
//

#include "mysqlpool.h"

void MySqlPool::init(const char *host, int port,
                     const char *user, const char *pwd, const char *dbName,
                     int connSize = 10) {
    assert(connSize > 0);
    for (int i = 0; i < connSize; i++) {
        MYSQL *sql = nullptr;
        sql = mysql_init(sql);
        if (!sql) {
            LOG_ERROR("MySql init error!");
            assert(sql);
        }
        sql = mysql_real_connect(sql, host, user, pwd, dbName, port, nullptr, 0);
        if (!sql) {
            LOG_ERROR("MySql Connect error!");
        }
        connQue_.push(sql);
    }
    MAX_CONN_ = connSize;
    sem_init(&semId_, 0, MAX_CONN_);
}

MySqlPool::MySqlPool() {
    useCount_ = 0;
    freeCount_ = 0;
}

MYSQL *MySqlPool::GetConn() {
    MYSQL *sql = nullptr;
    if (connQue_.empty()) {
        LOG_WARN("MySqlPool busy!");
        return nullptr;
    }
    sem_wait(&semId_);
    {
        std::lock_guard<std::mutex> locker(mtx_);
        sql = connQue_.front();
        connQue_.pop();
    }
    return sql;
}

void MySqlPool::FreeConn(MYSQL *sql) {
    assert(sql);
    std::lock_guard<std::mutex> locker(mtx_);
    connQue_.push(sql);
    sem_post(&semId_);
}

void MySqlPool::ClosePool() {
    std::lock_guard<std::mutex> locker(mtx_);
    while (!connQue_.empty()) {
        auto item = connQue_.front();
        connQue_.pop();
        mysql_close(item);
    }
    mysql_library_end();
}

int MySqlPool::GetFreeConnCount() {
    std::lock_guard<std::mutex> locker(mtx_);
    return connQue_.size();
}

MySqlPool::~MySqlPool() {
    ClosePool();
}