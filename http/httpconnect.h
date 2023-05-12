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

enum HTTP_STATUS_CODE {
    OK = 200,
    CREATED = 201,

    BAD_REQUEST = 400,
    FORBIDDEN = 403,
    NOT_FOUND = 404,

    INTERNAL_SERVER_ERROR = 500,

    NO_REQUEST = 0,
    GET_REQUEST,
    BAD_REQUEST,
    NO_RESOURSE,
    FORBIDDENT_REQUEST,
    FILE_REQUEST,
    INTERNAL_ERROR,
    CLOSED_CONNECTION,
};

struct ResponseMessage {
    std::optional<std::string> html_path_;
    HTTP_STATUS_CODE code_;
};


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

    static bool isET;
    static const char *srcDir;
    static std::atomic<int> userCount;

private:
    int fd_;
    struct sockaddr_in addr_;

    bool isClose_;

    int iovCnt_;
    struct iovec iov_[2];

    Buffer readBuff_; // 读缓冲区
    Buffer writeBuff_; // 写缓冲区

    HttpRequest request_;
    HttpResponse response_;

    /*
     * USER DEFINED FUNCS
     * */
    static bool userFuncsLoaded_;
    /*  GET请求对应的视图函数  */
    static std::unordered_map<std::string, std::function<ResponseMessage(std::string)>> GET_FUNC;
    /*  POST请求对应的视图函数  */
    static std::unordered_map<std::string,
            std::function<ResponseMessage(std::unordered_map<std::string, std::string>)>> POST_FUNC;

    static void loadUserFuncs_();

    ResponseMessage getResponse_();
};

#endif //WEBSERVER_HTTPCONNECT_H
