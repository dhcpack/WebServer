#include "server/webserver.h"
#include "config/config.h"

int main() {

    WebServer webServer(
            Config::port, Config::listenET, Config::connectET, Config::timeoutMS,
            Config::openLinger, Config::threadPoolNum,  // 端口，监听事件ET，连接事件ET，超时时间，优雅关闭，工作线程数量
            Config::useDatabase, Config::sqlhost, Config::sqlPort, Config::sqlUser, Config::sqlPwd,
            Config::dbName, Config::connPoolNum,  // 数据库
            Config::openLog, Config::logQueSize, Config::debugLog,  // 日志
            Config::resourcesDir);  // 网页资源目录

    // Error Check
    std::string error;
    if (webServer.hasError(error)) {
        std::cerr << error << std::endl;
        exit(-1);
    } else {
        std::cout << "========== Server start ==========" << std::endl;
        webServer.start();
    }
}