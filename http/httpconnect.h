//
// Created by ylhappy on 2023/5/11.
//

#ifndef WEBSERVER_HTTPCONNECT_H
#define WEBSERVER_HTTPCONNECT_H

#include <sys/types.h>
#include <sys/uio.h>     // readv/writev
#include <arpa/inet.h>   // sockaddr_in
#include <cstdlib>      // atoi()
#include <cerrno>

#include "../log/log.h"
#include "../buffer/buffer.h"
#include "httprequest.h"
#include "httpresponse.h"


/*
 * Http Connection
 * */
class HttpConnection {
public:
    HttpConnection();

    ~HttpConnection();

    void init(int sockFd, const sockaddr_in &addr);

    ssize_t read(int *saveErrno);

    ssize_t write(int *saveErrno);

    void close();

    int getFd() const;

    int getPort() const;

    const char *getIp() const;

    sockaddr_in getAddr() const;

    bool process();

    int toWriteBytes() {
        return iov_[0].iov_len + iov_[1].iov_len;
    }

    bool isKeepAlive() const {
        return request_.isKeepAlive();
    }

    /*
     * 静态，定义HttpConnect共同的配置
     * */
    static bool isET;
    static const char *srcDir;
    static std::atomic<int> userCount;

private:
    int fd_;
    struct sockaddr_in addr_;

    bool isClose_;

    int iovCnt_;
    struct iovec iov_[2];

    /*
     * 从读缓冲区读取request，将response写入写缓冲区中
     * */
    Buffer readBuff_;
    Buffer writeBuff_;

    HttpRequest request_;
    HttpResponse response_;
};

#endif //WEBSERVER_HTTPCONNECT_H
