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