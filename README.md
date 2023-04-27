# WebServer
Yuelin's WebServer

database-settings:
```cpp
string user = "ws";
string passwd = "123456";
string databasename = "webserver";
```
```mysql
create database webserver;

use webserver;

CREATE TABLE user(
    username char(50) NULL,
    passwd char(50) NULL
)ENGINE=InnoDB;

INSERT INTO user(username, passwd) VALUES('ylhappy', '123456');

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