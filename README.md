### WebServer

----

![GitHub](https://img.shields.io/github/license/dhcpack/WebServer)
![GitHub top language](https://img.shields.io/github/languages/top/dhcpack/WebServer)
![GitHub repo size](https://img.shields.io/github/repo-size/dhcpack/WebServer)
![GitHub Workflow Status (with branch)](https://img.shields.io/github/actions/workflow/status/dhcpack/WebServer/c-cpp.yml?branch=main)
![GitHub Repo stars](https://img.shields.io/github/stars/dhcpack/WebServer?style=social)


**使用C++11编写的轻量级高性能服务器，参考Linux高性能服务器编程（游双著）**
- **[阻塞队列](https://github.com/dhcpack/WebServer/tree/main/log)**：使用条件变量实现生产者消费者模式，使用互斥锁确保线程安全
- **[日志](https://github.com/dhcpack/WebServer/tree/main/log)**：借助阻塞队列实现异步日志，实现日志分级，日志格式参考IIS Web服务器默认格式
- **[线程池](https://github.com/dhcpack/WebServer/tree/main/threadpool)   [I/O复用](https://github.com/dhcpack/WebServer/tree/main/server)**：利用IO复用技术Epoll和线程池实现多线程的Reactor高并发模型
- **[数据库连接池](https://github.com/dhcpack/WebServer/tree/main/mysqlpool)**：利用RAII机制实现数据库连接池，减少数据库建立连接和初始化的开销
- **[定时器](https://github.com/dhcpack/WebServer/tree/main/timer)**：基于小根堆实现时间堆定时器，高效处理超时的非活动链接
- **[Http请求](https://github.com/dhcpack/WebServer/tree/main/http)**：使用状态机解析Http请求。可自定义并注册视图函数，也可处理对静态资源的请求
- **[Http响应](https://github.com/dhcpack/WebServer/tree/main/http)**：使用文件映射内存(mmap)，分散读、聚集写(iovec, readv, writev)加快响应速度
- **[配置文件](https://github.com/dhcpack/WebServer/tree/main/config)**：统一管理和自定义服务器的所有配置




**运行方法**
```bash
  cmake -S . -B build
  cmake --build build
```


### 参考
![](https://img.shields.io/badge/WebSite-http%3A%2F%2F43.143.166.142%3A1314%2F-brightgreen)