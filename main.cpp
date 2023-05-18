#include "server/webserver.h"

int main() {
    WebServer webServer(
            1314, 3, 60000, false,             /* 端口 ET模式 timeoutMs 优雅退出  */
            "43.143.166.142", 3306, "ws", "123456", "webserver", /* Mysql配置 */
            12, 6, true, 1024, false);             /* 连接池数量 线程池数量 日志开关 日志等级 日志异步队列容量 */

    std::string error;
    if (webServer.hasError(error)) {
        std::cerr << error << std::endl;
        exit(-1);
    } else {
        webServer.start();
    }
}