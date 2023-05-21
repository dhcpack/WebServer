### WebServer

![GitHub](https://img.shields.io/github/license/dhcpack/WebServer)
![GitHub top language](https://img.shields.io/github/languages/top/dhcpack/WebServer)
![GitHub repo size](https://img.shields.io/github/repo-size/dhcpack/WebServer)
![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/dhcpack/WebServer/c-cpp.yml?branch=main)
![GitHub Repo stars](https://img.shields.io/github/stars/dhcpack/WebServer?style=social)

----

**使用C++17编写的轻量级高性能服务器，参考Linux高性能服务器编程（游双著）**
- **[阻塞队列](https://github.com/dhcpack/WebServer/tree/main/log)**：使用条件变量实现生产者消费者模式，使用互斥锁确保线程安全
- **[日志](https://github.com/dhcpack/WebServer/tree/main/log)**：借助阻塞队列实现异步日志，实现日志分级，日志格式参考IIS Web服务器默认格式
- **[线程池](https://github.com/dhcpack/WebServer/tree/main/threadpool)   [I/O复用](https://github.com/dhcpack/WebServer/tree/main/server)**：利用IO复用技术Epoll和线程池实现多线程的Reactor高并发模型
- **[数据库连接池](https://github.com/dhcpack/WebServer/tree/main/mysqlpool)**：实现数据库连接池，减少数据库连接建立和初始化的开销。利用RAII机制管理数据库连接的获取和释放。实现数据库连接的超时重连。
- **[定时器](https://github.com/dhcpack/WebServer/tree/main/timer)**：基于小根堆实现时间堆定时器，高效处理超时的非活动连接
- **[Http请求](https://github.com/dhcpack/WebServer/tree/main/http)**：使用状态机解析Http请求。可自定义并注册视图函数，也可处理对静态资源的请求
- **[Http响应](https://github.com/dhcpack/WebServer/tree/main/http)**：使用文件映射内存(mmap)，分散读、聚集写(iovec, readv, writev)加快响应速度
- **[配置文件](https://github.com/dhcpack/WebServer/tree/main/config)**：统一管理和自定义服务器的所有配置

----

### 环境
```cmake
cmake_minimum_required(VERSION 3.23) 
```
确保安装了`mysqlclient`链接库，可通过以下命令安装
```shell
sudo apt-get install libmysqlclient-dev
```
在`Config.h`中配置数据库和静态资源目录，若计划使用注册和登录功能需要在数据库建立user表：
```mysql
CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;
```

----

### 运行方法
cmake项目
```bash
cmake -S . -B build
cmake --build build
./WebServer
```
默认运行在1314端口

----

### 架构
#### Epoll + Reactor

![reactor](docs/image/reactor.png)
**主线程只负责监听，工作线程做读写数据和处理客户端请求**

----

### 网站
[Yuelin's WebServer](http://43.143.166.142:1314/)

----

### 参考
- Linux高性能服务器编程（游双著）
- [qinguoyi/TinyWebServer](https://github.com/qinguoyi/TinyWebServer/)
- [markparticle/WebServer](https://github.com/markparticle/WebServer)