//
// Created by ylhappy on 2023/5/3.
//

#ifndef WEBSERVER_MYSQLMANAGER_H
#define WEBSERVER_MYSQLMANAGER_H

#include "mysqlpool.h"

class MySqlManager {
public:
    MySqlManager(MYSQL **sql) {
        *sql = MySqlPool::instance().getConn();
        sql_ = *sql;
    }

    ~MySqlManager() {
        MySqlPool::instance().freeConn(sql_);
    }

private:
    MYSQL *sql_;
};

#endif //WEBSERVER_MYSQLMANAGER_H
