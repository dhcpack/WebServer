# WebServer
Yuelin's WebServer

database-settings:
```cpp
string user = "ws";
string password = "123456";
string databasename = "webserver";
```
```mysql
create database webserver;

use webserver;

CREATE TABLE user(
    username char(50) NULL,
    password char(50) NULL
)ENGINE=InnoDB;

INSERT INTO user(username, password) VALUES('ylhappy', '123456');

```

**类定义中，可以声明静态成员变量，但不能对其进行初始化或赋值**
```cpp
static uint64_t MAX_FILE_LINE = 50000;  // error
```
这是因为类只是一个模板，类的静态成员变量是在程序运行时分配内存并初始化的，而不是在类定义中。

**但如果静态成员变量时`const`类型，则可以在编译期就确定其值，并替换为一个常量**
```cpp
static const uint64_t MAX_FILE_LINE = 50000;  // correct
```

**非静态成员变量的内存是在对象创建时分配的，并且每个对象都有其自己的成员变量。因此，当对象创建时，它的成员变量可以立即初始化或赋值。**

**静态成员变量的内存是在程序运行时分配的，而不是在对象创建时。因此，静态成员变量的初始化或赋值不能在类定义中进行，因为在这个时候，程序还没有开始运行，静态成员变量的内存还没有被分配。**

## 事件处理模式
- Reactor模式

  Reactor是这样一种模式，它要求主线程(I/O处理单元，下同)只负责监听文件描述上是否有事件发生，有的话就立即将该事件通知工作线程(逻辑单元，下同)。除此之外，主线程不做任何其他实质性的工作。读写数据，接受新的连接，以及处理客户请求均在工作线程中完成。

- Proactor模式

  与Reactor模式不同，Proactor模式将所有I/O操作都交给主线程和内核来处理，工作线程仅仅负责业务逻辑。


## 并发模式
- 半同步/半异步模式

  同步线程用于处理客户逻辑，异步线程用于处理I/O事件。

- 半同步/半反应堆(half-sync/half-reactive)模式


## I/O复用技术
I/O复用使得程序能同时监听多个文件描述符。

select系统调用的用途是：在一段指定时间内，监听用户感兴趣的文件描述符上的可读、可写和异常等事件。

poll系统调用和select类似，也是在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪者。

epoll是Linux特有的I/O复用函数。它在实现和使用上与select、poll有很大差异。首先，epoll使用一组函数来完成任务，而不是单个函数。其次，epoll把用户关心的文件描述符上的事件放在内核里的一个事件表中，从而无须像select和poll那样每次调用都要重复传入文件描述符集或事件集。但epoll需要使用一个额外的文件描述符，来唯一标识内核中的这个事件表。这个文件描述符使用epoll create函数来创建。

epoll对文件描述符的操作有两种模式：LT(Level Trigger,电平触发)模式和ET(EdgeTrigger,边沿触发)模式。LT模式是默认的工作模式，这种模式下epoll相当于一个效率较高的poll。当往epoll内核事件表中注册一个文件描述符上的EPOLLET事件时，epoll将以ET模式来操作该文件描述符。ET模式是epoll的高效工作模式。


### pressure test
```bash
#./webbench -c 1005 -t 5 http://43.143.166.142:1314/speed.html
ab -n 10000 -c 1000 http://43.143.166.142:1314/speed.html
```

### MySql
```mysql
show global variables like '%wait_timeout%';  # 超时时间
show processlist;  # 查看连接
```