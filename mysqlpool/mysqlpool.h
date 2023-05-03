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
    void init(const char *host, int port, const char *user, const char *pwd, const char *dbName, int connSize);

    static MySqlPool *Instance();

    MYSQL *GetConn();

    void FreeConn(MYSQL *conn);

    int GetFreeConnCount();

    void ClosePool();

private:
    MySqlPool();

    ~MySqlPool();

    int MAX_CONN_;
    int useCount_;
    int freeCount_;

    std::queue<MYSQL *> connQue_;
    std::mutex mtx_;
    sem_t semId_;
};

#endif //WEBSERVER_MYSQLPOOL_H
