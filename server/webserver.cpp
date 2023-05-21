//
// Created by ylhappy on 2023/5/11.
//

#include "webserver.h"
#include <iostream>

WebServer::WebServer(
        uint16_t port, uint32_t listenET, uint32_t connectET, int timeoutMS, bool OptLinger, uint16_t threadPoolNum,
        bool useDataBase, const char *sqlhost, uint16_t sqlPort, const char *sqlUser, const char *sqlPwd,
        const char *dbName, uint16_t connPoolNum,
        bool openLog, uint32_t logQueSize, bool debugLog, const char* resourcesDir) :
        port_(port), openLinger_(OptLinger), timeoutMS_(timeoutMS), isClose_(false),
        timer_(new HeapTimer()), threadpool_(new ThreadPool(threadPoolNum)), epoller_(new Epoller()) {
    // 初始化日志
    if (openLog) {
        if (!Log::instance().init(logQueSize)) {
            started_ = false, error_ = "========== Log init Failed ==========";
            return;
        }
        Log::debugLog = debugLog;
    }
    // 初始化数据库
    if (useDataBase) {
        LOG_DEBUG("========== MySql init ==========\n");
        if (!MySqlPool::instance().init(sqlhost, sqlPort, sqlUser, sqlPwd, dbName, connPoolNum)) {
            started_ = false, error_ = "========== MySql init Failed ==========";
            return;
        }
        LOG_DEBUG("========== MySql ok ==========\n");
    } else {
        LOG_DEBUG("No Database\n");
    }


    srcDir_ = getcwd(nullptr, 256);
    assert(srcDir_);
    strncat(srcDir_, resourcesDir, 20);
    HttpConnection::userCount = 0;
    HttpConnection::srcDir = srcDir_;

    // 初始化触发模式
    // 关闭链接触发 + 一次触发
    listenEvent_ = EPOLLRDHUP | listenET;  // 监听事件配置
    connEvent_ = EPOLLONESHOT | EPOLLRDHUP | connectET;  // 连接事件配置
    HttpConnection::isET = (connEvent_ & EPOLLET);  // 边缘触发连接

    LOG_DEBUG("========== Socket init ==========\n");
    // 初始化端口
    if (!initSocket_(threadPoolNum)) {
        isClose_ = true;
        started_ = false, error_ = "========== Socket init Failed ==========";
        return;
    }
    LOG_DEBUG("========== Socket ok ==========\n");
}

WebServer::~WebServer() {
    close(listenFd_);
    isClose_ = true;
    free(srcDir_);
    MySqlPool::instance().ClosePool();
}

// 初始化监听套接字
bool WebServer::initSocket_(u_int32_t threadNum) {
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
        optLinger.l_onoff = 1;  // 优雅关闭
        optLinger.l_linger = Config::lingerDelayTime;  // 延迟时间1s
    }

    // 创建套接字
    listenFd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listenFd_ < 0) {
        LOG_FATAL("Create socket error!\n", port_);
        return false;
    }

    // 设置套接字的SO_LINGER选项，启动优雅关闭
    ret = setsockopt(listenFd_, SOL_SOCKET, SO_LINGER, &optLinger, sizeof(optLinger));
    if (ret < 0) {
        close(listenFd_);
        LOG_FATAL("SO_LINGER set error!\n", port_);
        return false;
    }

    int optval = 1;
    // 设置套接字的地址重用选项(SO_REUSEADDR)，启动地址重用
    ret = setsockopt(listenFd_, SOL_SOCKET, SO_REUSEADDR, (const void *) &optval, sizeof(int));
    if (ret == -1) {
        LOG_FATAL("SO_REUSEADDR set error!\n");
        close(listenFd_);
        return false;
    }

    // 绑定套接字到端口
    ret = bind(listenFd_, (struct sockaddr *) &addr, sizeof(addr));
    if (ret < 0) {
        LOG_FATAL("Bind Port:[%d] error!\n", port_);
        close(listenFd_);
        return false;
    }

    // 监听套接字
    ret = listen(listenFd_, threadNum);
    if (ret < 0) {
        LOG_FATAL("Listen port:[%d] error!\n", port_);
        close(listenFd_);
        return false;
    }

    // 在epoller中监听
    ret = epoller_->addFd(listenFd_, listenEvent_ | EPOLLIN);
    if (ret == 0) {
        LOG_FATAL("Add listen fd error!\n");
        close(listenFd_);
        return false;
    }

    // 设置套接字为非阻塞式
    setFdNonblock_(listenFd_);
    LOG_DEBUG("Server port:[%d]\n", port_);
    return true;
}

void WebServer::start() {
    int timeMS = -1;  // -1 == infinite
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
            if (fd == listenFd_) {  // 新的连接请求：时间描述符是监听的socket
                dealListen_();
            } else if (events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {  // 连接异常，关闭连接
                assert(users_.count(fd) > 0);
                closeConnection_(&users_[fd]);
            } else if (events & EPOLLIN) {  // 有数据可读
                assert(users_.count(fd) > 0);
                dealRead_(&users_[fd]);
            } else if (events & EPOLLOUT) {  // 有数据可写
                assert(users_.count(fd) > 0);
                dealWrite_(&users_[fd]);
            } else {
                LOG_ERROR("Unexpected event!\n");
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

// 关闭连接
void WebServer::closeConnection_(HttpConnection *client) {
    assert(client);
    epoller_->delFd(client->getFd());
    client->close_();
}

// 添加连接
void WebServer::addClient_(int fd, sockaddr_in addr) {
    assert(fd > 0);
    users_[fd].init(fd, addr);
    if (timeoutMS_ > 0) {
        timer_->push(fd, timeoutMS_, std::bind(&WebServer::closeConnection_, this, &users_[fd]));
    }
    epoller_->addFd(fd, EPOLLIN | connEvent_);
    setFdNonblock_(fd);  // 非阻塞
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
    if (client->process()) {  // 返回信息已生成--注册到写事件，下次检查时间是否可写 EPOLLOUT 写事件，想要向客户端发回数据
        epoller_->modFd(client->getFd(), connEvent_ | EPOLLOUT);
    } else {  // 注册到读事件，下次检查时间是否可读 EPOLLIN 读事件
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

bool WebServer::hasError(std::string &error) {
    if (started_) return false;
    else {
        error = error_;
        return true;
    }
}