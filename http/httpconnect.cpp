//
// Created by ylhappy on 2023/5/11.
//

#include "httpconnect.h"

const char *HttpConnection::srcDir;
std::atomic<int> HttpConnection::userCount;
bool HttpConnection::isET;

HttpConnection::HttpConnection() {
    fd_ = -1;
    addr_ = {0};
    isClose_ = true;
};

HttpConnection::~HttpConnection() {
    close_();
};

void HttpConnection::init(int fd, const sockaddr_in &addr) {
    assert(fd > 0);
    userCount++;
    addr_ = addr;
    fd_ = fd;
    writeBuff_.RetrieveAll();
    readBuff_.RetrieveAll();
    isClose_ = false;
    LOG_DEBUG("Client[%d](%s:%d) connected, userCount:%d\n", fd_, getIp(), getPort(), (int) userCount);
}

void HttpConnection::close_() {
    response_.unmapFile();
    if (!isClose_) {
        isClose_ = true;
        userCount--;
        close(fd_);
        LOG_DEBUG("Client[%d](%s:%d) quit, UserCount:%d\n", fd_, getIp(), getPort(), (int) userCount);
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

bool HttpConnection::process() {
    request_.clear();
    if (readBuff_.ReadableBytes() <= 0) return false;

    // Parse request
    bool parseResult = request_.parse(readBuff_);
    response_.init(srcDir, request_.isKeepAlive(), !parseResult, request_.method(), request_.path(), request_.post());

    // Make response
    response_.makeResponse(writeBuff_);

    // 输出响应头
    iov_[0].iov_base = const_cast<char *>(writeBuff_.Peek());
    iov_[0].iov_len = writeBuff_.ReadableBytes();
    iovCnt_ = 1;

    // 输出文件
    if (response_.fileLen() > 0 && response_.file()) {
        iov_[1].iov_base = response_.file();
        iov_[1].iov_len = response_.fileLen();
        iovCnt_ = 2;
    }
    if (parseResult) {
        LOG_INFO("%s:%d %s %s HTTP/%s %d %d\n", getIp(), getPort(), request_.getMethod().c_str(),
                 request_.path().c_str(), request_.version().c_str(), response_.code(),
                 iovCnt_ == 2 ? iov_[0].iov_len + iov_[1].iov_len : iov_[0].iov_len);
    }

    LOG_DEBUG("filesize:%d, %d  to %d\n", response_.fileLen(), iovCnt_, toWriteBytes());
    return true;
}
