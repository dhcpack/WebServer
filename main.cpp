#include <iostream>
#include "./log/log.h"
#include "http/httprequest.h"

using namespace std;

int main() {
    Log &log = Log::instance();
    if (!log.init()) return -1;

    LOG_DEBUG("Initializing MysqlPool ...\n");
    MySqlPool &mySqlPool = MySqlPool::instance();
    if (mySqlPool.init("127.0.0.1", 3306, "ws", "123456", "webserver", 10)) {
        LOG_DEBUG("MySqlPool initialize succeed!\n");
    } else {
        LOG_FATAL("MySqlPool initialize failed!\n");
        return -2;
    }

    std::unordered_map<std::string, std::string> userinfo;
    userinfo["username"] = "ylhappy";
    userinfo["password"] = "123456";
    std::string log_info = post_login(userinfo);
    std::cout << log_info << std::endl;
    log_info = post_register(userinfo);
    std::cout << log_info << std::endl;
    userinfo["username"] = "yl";
    log_info = post_register(userinfo);
    std::cout << log_info << std::endl;
    /*
     * httpRequest NOT tested
     * */
    // HttpRequest httpRequest;
    // httpRequest.parse()
    cout << "Finished!" << endl;
    return 0;
}