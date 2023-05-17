//
// Created by ylhappy on 2023/5/11.
//

#ifndef WEBSERVER_WEBSERVER_H
#define WEBSERVER_WEBSERVER_H

#include "../log/log.h"
#include "../http/httpconnect.h"
#include "../mysqlpool/mysqlpool.h"
#include "epoller.h"
#include "../timer/heaptimer.h"
#include "../threadpool/threadpool.h"


class WebServer {
public:
    WebServer(
            int port, int trigMode, int timeoutMS, bool OptLinger,
            int sqlPort, const char *sqlUser, const char *sqlPwd,
            const char *dbName, int connPoolNum, int threadNum,
            bool openLog, int logLevel, int logQueSize);

    ~WebServer();

    void start();

private:
    bool initSocket_();

    void initEventMode_(int trigMode);

    void addClient_(int fd, sockaddr_in addr);

    void dealListen_();

    void dealWrite_(HttpConnection *client);

    void dealRead_(HttpConnection *client);

    void sendError_(int fd, const char *info);

    void extentTime_(HttpConnection *client);

    void closeConnection_(HttpConnection *client);

    void onRead_(HttpConnection *client);

    void onWrite_(HttpConnection *client);

    void onProcess_(HttpConnection *client);

    static const int MAX_FD = 65536;

    static int setFdNonblock_(int fd);

    int port_;
    bool openLinger_;
    int timeoutMS_;  /* 毫秒MS */
    bool isClose_;
    int listenFd_;
    char *srcDir_;

    uint32_t listenEvent_;
    uint32_t connEvent_;

    std::unique_ptr<HeapTimer> timer_;
    std::unique_ptr<ThreadPool> threadpool_;
    std::unique_ptr<Epoller> epoller_;
    std::unordered_map<int, HttpConnection> users_;
};

#endif //WEBSERVER_WEBSERVER_H
