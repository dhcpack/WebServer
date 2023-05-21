//
// Created by ylhappy on 2023/4/26.
//

#ifndef WEBSERVER_CONFIG_H
#define WEBSERVER_CONFIG_H

#include <iostream>
#include "../server/epoller.h"

/*
 * Write Your Config here
 * */
namespace Config {
    /*
     * 服务器
     * */
    // 服务器端口
    static const uint16_t port = 1314;
    // 断开连接时间 (ms) (-1 == infinite)
    static const int timeoutMS = 60000;
    // 是否优雅关闭
    static const bool openLinger = false;
    // 优雅关闭延迟时间 (s)
    static const uint32_t lingerDelayTime = 1;
    // 监听事件边缘触发 (EPOLLET: Edge Trigger, 0: Level Trigger)
    static const uint32_t listenET = EPOLLET;
    // 连接事件边缘触发 (EPOLLET: Edge Trigger, 0: Level Trigger)
    static const uint32_t connectET = EPOLLET;
    // 工作线程数量
    static const uint16_t threadPoolNum = 20;
    // 网页资源目录
    static const char *resourcesDir = "/../resources";


    /*
     * 数据库
     * */
    // 使用数据库
    static const bool useDatabase = true;
    // 数据库主机
    static const char *sqlhost = "43.143.166.142";
    // 数据库端口
    static const uint16_t sqlPort = 3306;
    // 数据库用户
    static const char *sqlUser = "ws";
    // 数据库密码
    static const char *sqlPwd = "rJBn4XixtdpsbdrD";
    // 数据库名称
    static const char *dbName = "webserver";
    // 数据库连接池大小
    static const uint16_t connPoolNum = 12;


    /*
     * 日志
     * */
    // 使用日志
    static const bool openLog = true;
    // 日志缓冲队列大小
    static const uint32_t logQueSize = 1024;
    // 输出Debug级日志
    static const bool debugLog = false;
    // 日志文件最大行数
    static const uint64_t maxLogLine = 500000;
}


#endif //WEBSERVER_CONFIG_H
