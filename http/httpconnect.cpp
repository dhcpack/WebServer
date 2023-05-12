//
// Created by ylhappy on 2023/5/11.
//

#include "httpconnect.h"

/*
 * 初始化类的静态变量
 * */
bool HttpConnection::userFuncsLoaded_ = false;
/*  GET请求对应的视图函数  */
std::unordered_map<std::string, std::function<ResponseMessage(std::string)>> HttpConnection::GET_FUNC{};
/*  POST请求对应的视图函数  */
std::unordered_map<std::string, std::function<ResponseMessage(
        std::unordered_map<std::string, std::string>)>> HttpConnection::POST_FUNC{};


const char *HttpConnection::srcDir;
std::atomic<int> HttpConnection::userCount;
bool HttpConnection::isET;

HttpConnection::HttpConnection() {
    fd_ = -1;
    addr_ = {0};
    isClose_ = true;
};

HttpConnection::~HttpConnection() {
    close();
};

void HttpConnection::loadUserFuncs_() {
    // load GET_FUNC
    GET_FUNC["/index"] = get_index, GET_FUNC["/welcome"] = get_welcome, GET_FUNC["/video"] = get_video;
    GET_FUNC["/picture"] = get_picture, GET_FUNC["/register"] = get_register, GET_FUNC["/login"] = get_login;

    // load POST_FUNC
    POST_FUNC["/login"] = post_login, POST_FUNC["/register"] = post_register;
    userFuncsLoaded_ = true;
}

void HttpConnection::init(int fd, const sockaddr_in &addr) {
    if (!userFuncsLoaded_) loadUserFuncs_();
    assert(fd > 0);
    userCount++;
    addr_ = addr;
    fd_ = fd;
    writeBuff_.RetrieveAll();
    readBuff_.RetrieveAll();
    isClose_ = false;
    LOG_INFO("Client[%d](%s:%d) in, userCount:%d", fd_, getIp(), getPort(), (int) userCount);
}

void HttpConnection::close() {
    response_.unmapFile();
    if (isClose_ == false) {
        isClose_ = true;
        userCount--;
        ::close(fd_);
        LOG_INFO("Client[%d](%s:%d) quit, UserCount:%d", fd_, getIp(), getPort(), (int) userCount);
    }
}

int HttpConnection::getFd() const {
    return fd_;
};

struct sockaddr_in HttpConnection::getAddr() const {
    return addr_;
}

const char *HttpConnection::getIp() const {
    return inet_ntoa(addr_.sin_addr);
}

int HttpConnection::getPort() const {
    return addr_.sin_port;
}

ssize_t HttpConnection::read(int *saveErrno) {
    ssize_t len = -1;
    do {
        len = readBuff_.ReadFd(fd_, saveErrno);
        if (len <= 0) {
            break;
        }
    } while (isET);
    return len;
}

ssize_t HttpConnection::write(int *saveErrno) {
    ssize_t len = -1;
    do {
        len = writev(fd_, iov_, iovCnt_);
        if (len <= 0) {
            *saveErrno = errno;
            break;
        }
        if (iov_[0].iov_len + iov_[1].iov_len == 0) { break; } /* 传输结束 */
        else if (static_cast<size_t>(len) > iov_[0].iov_len) {
            iov_[1].iov_base = (uint8_t *) iov_[1].iov_base + (len - iov_[0].iov_len);
            iov_[1].iov_len -= (len - iov_[0].iov_len);
            if (iov_[0].iov_len) {
                writeBuff_.RetrieveAll();
                iov_[0].iov_len = 0;
            }
        } else {
            iov_[0].iov_base = (uint8_t *) iov_[0].iov_base + len;
            iov_[0].iov_len -= len;
            writeBuff_.Retrieve(len);
        }
    } while (isET || toWriteBytes() > 10240);
    return len;
}

ResponseMessage HttpConnection::getResponse_() {
    if (request_.path() == "/") {  // default html
        return {"/index.html", HTTP_STATUS_CODE::OK};
    } else if (request_.method() == "GET") {
        if (GET_FUNC.count(request_.path())) return GET_FUNC[request_.path()](request_.path());
        else return {"/404.html", HTTP_STATUS_CODE::NOT_FOUND};
    } else if (request_.method() == "POST") {
        if (POST_FUNC.count(request_.path())) return POST_FUNC[request_.path()](request_.post());
        else return {"/404.html", HTTP_STATUS_CODE::NOT_FOUND};
    } else return {"/404.html", HTTP_STATUS_CODE::NOT_FOUND};
}

bool HttpConnection::process() {
    request_.clear();
    if (readBuff_.ReadableBytes() <= 0) {
        return false;
    } else if (request_.parse(readBuff_)) {
        LOG_DEBUG("%s", request_.path().c_str());
        ResponseMessage responseMessage = getResponse_();
        response_.init(srcDir, responseMessage.html_path_.value(), request_.isKeepAlive(), responseMessage.code_);
    } else {
        response_.init(srcDir, request_.path(), false, HTTP_STATUS_CODE::BAD_REQUEST);
    }


    response_.makeResponse(writeBuff_);
    /* 响应头 */
    iov_[0].iov_base = const_cast<char *>(writeBuff_.Peek());
    iov_[0].iov_len = writeBuff_.ReadableBytes();
    iovCnt_ = 1;

    /* 文件 */
    if (response_.fileLen() > 0 && response_.file()) {
        iov_[1].iov_base = response_.file();
        iov_[1].iov_len = response_.fileLen();
        iovCnt_ = 2;
    }
    LOG_DEBUG("filesize:%d, %d  to %d", response_.fileLen(), iovCnt_, toWriteBytes());
    return true;
}
