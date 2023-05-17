//
// Created by ylhappy on 2023/5/3.
//

#include "mysqlpool.h"

bool MySqlPool::init(const char *host, uint16_t port, const char *user, const char *pwd, const char *dbName,
                     size_t connSize) {
    for (int i = 0; i < connSize; i++) {
        MYSQL *sql;
        if ((sql = mysql_init(nullptr)) == nullptr) {
            LOG_FATAL("MySql init error: %s\n", mysql_error(sql));
            return false;
        }
        if ((mysql_real_connect(sql, host, user, pwd, dbName, port, nullptr, 0)) == nullptr) {
            LOG_FATAL("MySql connect error: %s\n", mysql_error(sql));
            return false;
        }
        connQueue_.push(sql);
    }
    MAX_CONNECTIONS = connSize;
    sem_init(&sem_, 0, MAX_CONNECTIONS);
    return true;
}

MySqlPool &MySqlPool::instance() {
    static MySqlPool mySqlPool;
    return mySqlPool;
}

MYSQL *MySqlPool::getConn() {
    MYSQL *sql = nullptr;
    if (connQueue_.empty()) {
        LOG_WARN("MySqlPool busy!");
        return nullptr;
    }
    sem_wait(&sem_);
    {
        std::lock_guard<std::mutex> locker(mutex_);
        sql = connQueue_.front();
        connQueue_.pop();
    }
    return sql;
}

void MySqlPool::freeConn(MYSQL *conn) {
    if (conn == nullptr) return;
    std::lock_guard<std::mutex> locker(mutex_);
    connQueue_.push(conn);
    sem_post(&sem_);
}

void MySqlPool::ClosePool() {
    std::lock_guard<std::mutex> locker(mutex_);
    while (!connQueue_.empty()) {
        auto item = connQueue_.front();
        connQueue_.pop();
        mysql_close(item);
    }
    mysql_library_end();
    sem_destroy(&sem_);
}

size_t MySqlPool::GetFreeConnCount() {
    std::lock_guard<std::mutex> locker(mutex_);
    return connQueue_.size();
}

MySqlPool::~MySqlPool() {
    ClosePool();
}