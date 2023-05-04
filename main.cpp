#include <iostream>
#include "./log/log.h"
#include "http/httprequest.h"

using namespace std;

int main() {
    Log &log = Log::instance();
    if (log.init()) {
        LOG_INFO("Log init Succeed\n");
    } else return -1;

    LOG_INFO("init MySqlPool ...\n");
    MySqlPool &mySqlPool = MySqlPool::instance();
    if (mySqlPool.init("127.0.0.1", 3306, "ws", "123456", "webserver", 10)) {
        LOG_INFO("MySqlPool init Succeed!\n");
    } else return -2;

    /*
     * httpRequest NOT tested
     * */
//    HttpRequest httpRequest;
//    httpRequest.parse()
    cout << "Succeed!" << endl;
    return 0;
}