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
            uint16_t port, uint32_t listenET, uint32_t connectET, int timeoutMS, bool OptLinger, uint16_t threadPoolNum,
            bool useDataBase, const char *sqlhost, uint16_t sqlPort, const char *sqlUser, const char *sqlPwd,
            const char *dbName, uint16_t connPoolNum,
            bool openLog, uint32_t logQueSize, bool debugLog);

    ~WebServer();

    bool hasError(std::string &error);

    void start();

private:
    bool initSocket_(uint32_t threadNum);

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
    int timeoutMS_;
    bool isClose_;
    int listenFd_;
    char *srcDir_;
    std::string error_;
    bool started_;

    uint32_t listenEvent_;
    uint32_t connEvent_;

    std::unique_ptr<HeapTimer> timer_;
    std::unique_ptr<ThreadPool> threadpool_;
    std::unique_ptr<Epoller> epoller_;
    std::unordered_map<int, HttpConnection> users_;
};

#endif //WEBSERVER_WEBSERVER_H
