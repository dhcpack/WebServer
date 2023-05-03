//
// Created by ylhappy on 2023/5/3.
//

#ifndef WEBSERVER_MYSQLPOOL_H
#define WEBSERVER_MYSQLPOOL_H

#include <mysql/mysql.h>
#include <string>
#include <queue>
#include <mutex>
#include <semaphore.h>
#include <thread>
#include "../log/log.h"

class MySqlPool {
public:
    /*
     * init must be called first
     * */
    bool init(const char *host, uint16_t port, const char *user, const char *pwd, const char *dbName, size_t connSize);

    static MySqlPool &instance();

    MYSQL *getConn();

    void freeConn(MYSQL *conn);

    size_t GetFreeConnCount();

    void ClosePool();

private:
    MySqlPool() = default;

    ~MySqlPool();

    size_t MAX_CONNECTIONS;

    std::queue<MYSQL *> connQueue_;
    std::mutex mutex_;
    sem_t semId_;
};

#endif //WEBSERVER_MYSQLPOOL_H
