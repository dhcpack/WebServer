#include <iostream>
#include <thread>
#include "./log/log.h"
#include "./mysqlpool/mysqlpool.h"

using namespace std;

int main() {
    Log &log = Log::instance();
    if (log.init()) {
        LOG_INFO("Log Init Succeed\n");
    } else return -1;

    LOG_INFO("Init MySqlPool ...\n");
    MySqlPool &mySqlPool = MySqlPool::instance();
    if (mySqlPool.init("127.0.0.1", 3306, "ws", "123456", "webserver", 10)) {
        LOG_INFO("MySql init Succeed\n");
    } else return -2;
    cout << "Succeed!" << endl;
    return 0;
}