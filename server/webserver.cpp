//
// Created by ylhappy on 2023/5/11.
//

#include "webserver.h"
#include <iostream>

WebServer::WebServer(
        int port, int trigMode, int timeoutMS, bool OptLinger,
        const char *sqlhost, int sqlPort, const char *sqlUser, const char *sqlPwd,
        const char *dbName, int connPoolNum, int threadNum,
        bool openLog, uint32_t logQueSize) :
        port_(port), openLinger_(OptLinger), timeoutMS_(timeoutMS), isClose_(false),
        timer_(new HeapTimer()), threadpool_(new ThreadPool(threadNum)), epoller_(new Epoller()) {
    // 初始化日志
    if (openLog)
        if (!Log::instance().init(logQueSize)) exit(-1);
    LOG_DEBUG("========== MySql init ==========\n");
    // 初始化数据库
    if (!MySqlPool::instance().init(sqlhost, sqlPort, sqlUser, sqlPwd, dbName, connPoolNum)) {
        LOG_FATAL("========== MySql init Failed ==========\n");
    }
    LOG_DEBUG("========== MySql ok ==========\n");

    srcDir_ = getcwd(nullptr, 256);
    assert(srcDir_);
    strncat(srcDir_, "/../resources", 16);  // For clion
    HttpConnection::userCount = 0;
    HttpConnection::srcDir = srcDir_;

    // 初始化触发模式
    initEventMode_(trigMode);
    LOG_DEBUG("========== Socket init ==========\n");
    // 初始化端口
    if (!initSocket_()) {
        isClose_ = true;
        LOG_FATAL("========== Socket init Failed ==========\n");
    }
    LOG_DEBUG("========== Socket ok ==========\n");
}

WebServer::~WebServer() {
    close(listenFd_);
    isClose_ = true;
    free(srcDir_);
    MySqlPool::instance().ClosePool();
}

void WebServer::initEventMode_(int trigMode) {
    // EPOLLONESHOT: 一次触发
    // EPOLLRDHUP: 监听或连接的对端关闭了连接
    listenEvent_ = EPOLLRDHUP;
    connEvent_ = EPOLLONESHOT | EPOLLRDHUP;
    switch (trigMode) {
        case 0:
            break;
        case 1:
            connEvent_ |= EPOLLET;
            break;
        case 2:
            listenEvent_ |= EPOLLET;
            break;
        case 3:
            listenEvent_ |= EPOLLET;
            connEvent_ |= EPOLLET;
            break;
        default:
            listenEvent_ |= EPOLLET;
            connEvent_ |= EPOLLET;
            break;
    }
    HttpConnection::isET = (connEvent_ & EPOLLET);
}

// 监听端口
bool WebServer::initSocket_() {
    int ret;
    struct sockaddr_in addr;
    if (port_ > 65535 || port_ < 1024) {
        LOG_FATAL("Port:[%d] is invalid!\n", port_);
        return false;
    }
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port_);
    struct linger optLinger = {0};
    if (openLinger_) {
        /* 优雅关闭: 直到所剩数据发送完毕或超时 */
        optLinger.l_onoff = 1;
        optLinger.l_linger = 1;
    }

    listenFd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd_ < 0) {
        LOG_FATAL("Create socket error!\n", port_);
        return false;
    }

    ret = setsockopt(listenFd_, SOL_SOCKET, SO_LINGER, &optLinger, sizeof(optLinger));
    if (ret < 0) {
        close(listenFd_);
        LOG_FATAL("Init linger error!\n", port_);
        return false;
    }

    int optval = 1;
    /* 端口复用 */
    /* 只有最后一个套接字会正常接收数据。 */
    ret = setsockopt(listenFd_, SOL_SOCKET, SO_REUSEADDR, (const void *) &optval, sizeof(int));
    if (ret == -1) {
        LOG_FATAL("set socket setsockopt error!\n");
        close(listenFd_);
        return false;
    }

    ret = bind(listenFd_, (struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0) {
        LOG_FATAL("Bind Port:[%d] error!\n", port_);
        close(listenFd_);
        return false;
    }

    ret = listen(listenFd_, 6);
    if (ret < 0) {
        LOG_FATAL("Listen port:[%d] error!\n", port_);
        close(listenFd_);
        return false;
    }
    ret = epoller_->addFd(listenFd_, listenEvent_ | EPOLLIN);
    if (ret == 0) {
        LOG_FATAL("Add listen error!\n");
        close(listenFd_);
        return false;
    }
    setFdNonblock_(listenFd_);
    LOG_DEBUG("Server port:[%d]\n", port_);
    return true;
}

void WebServer::start() {
    int timeMS = -1;  /* epoll wait timeout == -1 无事件将阻塞 */
    if (!isClose_) { LOG_INFO("========== Server start ==========\n"); }
    while (!isClose_) {
        if (timeoutMS_ > 0) {
            timeMS = timer_->getNextTick();
        }
        int eventCnt = epoller_->wait(timeMS);
        for (int i = 0; i < eventCnt; i++) {
            /* 处理事件 */
            int fd = epoller_->getEventFd(i);
            uint32_t events = epoller_->getEvents(i);
            if (fd == listenFd_) {
                dealListen_();
            } else if (events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                assert(users_.count(fd) > 0);
                closeConnection_(&users_[fd]);
            } else if (events & EPOLLIN) {
                assert(users_.count(fd) > 0);
                dealRead_(&users_[fd]);
            } else if (events & EPOLLOUT) {
                assert(users_.count(fd) > 0);
                dealWrite_(&users_[fd]);
            } else {
                LOG_ERROR("Unexpected event");
            }
        }
    }
}

void WebServer::sendError_(int fd, const char *info) {
    assert(fd > 0);
    int ret = send(fd, info, strlen(info), 0);
    if (ret < 0) {
        LOG_WARN("send error to client[%d] error!\n", fd);
    }
    close(fd);
}

void WebServer::closeConnection_(HttpConnection *client) {
    assert(client);
    LOG_INFO("Client[%d] quit!\n", client->getFd());
    epoller_->delFd(client->getFd());
    client->close();
}

void WebServer::addClient_(int fd, sockaddr_in addr) {
    assert(fd > 0);
    users_[fd].init(fd, addr);
    if (timeoutMS_ > 0) {
        timer_->push(fd, timeoutMS_, std::bind(&WebServer::closeConnection_, this, &users_[fd]));
    }
    epoller_->addFd(fd, EPOLLIN | connEvent_);
    setFdNonblock_(fd);
    LOG_INFO("Client[%d] in!\n", users_[fd].getFd());
}

void WebServer::dealListen_() {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    do {
        int fd = accept(listenFd_, (struct sockaddr *) &addr, &len);
        if (fd <= 0) { return; }
        else if (HttpConnection::userCount >= MAX_FD) {
            sendError_(fd, "Server busy!\n");
            LOG_WARN("Clients is full!\n");
            return;
        }
        addClient_(fd, addr);
    } while (listenEvent_ & EPOLLET);
}

void WebServer::dealRead_(HttpConnection *client) {
    assert(client);
    extentTime_(client);
    threadpool_->addTask(std::bind(&WebServer::onRead_, this, client));
}

void WebServer::dealWrite_(HttpConnection *client) {
    assert(client);
    extentTime_(client);
    threadpool_->addTask(std::bind(&WebServer::onWrite_, this, client));
}

void WebServer::extentTime_(HttpConnection *client) {
    assert(client);
    if (timeoutMS_ > 0) { timer_->refresh(client->getFd(), timeoutMS_); }
}

void WebServer::onRead_(HttpConnection *client) {
    assert(client);
    int ret = -1;
    int readErrno = 0;
    ret = client->read(&readErrno);
    if (ret <= 0 && readErrno != EAGAIN) {
        closeConnection_(client);
        return;
    }
    onProcess_(client);
}

void WebServer::onProcess_(HttpConnection *client) {
    if (client->process()) {
        epoller_->modFd(client->getFd(), connEvent_ | EPOLLOUT);
    } else {
        epoller_->modFd(client->getFd(), connEvent_ | EPOLLIN);
    }
}

void WebServer::onWrite_(HttpConnection *client) {
    assert(client);
    int ret = -1;
    int writeErrno = 0;
    ret = client->write(&writeErrno);
    if (client->toWriteBytes() == 0) {
        /* 传输完成 */
        if (client->isKeepAlive()) {
            onProcess_(client);
            return;
        }
    } else if (ret < 0) {
        if (writeErrno == EAGAIN) {
            /* 继续传输 */
            epoller_->modFd(client->getFd(), connEvent_ | EPOLLOUT);
            return;
        }
    }
    closeConnection_(client);
}

int WebServer::setFdNonblock_(int fd) {
    assert(fd > 0);
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
}


//int serve() {
//    Log &log = Log::instance();
//    if (!log.init()) return -1;
//
//    LOG_DEBUG("Initializing MysqlPool ...\n");
//    MySqlPool &mySqlPool = MySqlPool::instance();
//    if (mySqlPool.init("127.0.0.1", 3306, "ws", "123456", "webserver", 10)) {
//        LOG_DEBUG("MySqlPool initialize succeed!\n");
//    } else {
//        LOG_FATAL("MySqlPool initialize failed!\n");
//        return -2;
//    }
//
//    std::unordered_map<std::string, std::string> userinfo;
//    userinfo["username"] = "ylhappy";
//    userinfo["password"] = "123456";
//    std::string log_info = post_login(userinfo);
//    std::cout << log_info << std::endl;
//    log_info = post_register(userinfo);
//    std::cout << log_info << std::endl;
//    userinfo["username"] = "yl";
//    log_info = post_register(userinfo);
//    std::cout << log_info << std::endl;
///*
// * httpRequest NOT tested
// * */
//// HttpRequest httpRequest;
//// httpRequest.parse()
//    return 0;
//}