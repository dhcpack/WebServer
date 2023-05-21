### 阻塞队列
- 模板类[blockqueue.h](https://github.com/dhcpack/WebServer/blob/main/log/blockqueue.h)
- 线程安全的阻塞队列 
- RAII模式 
- 使用互斥锁 
- 使用条件变量实现**生产者、消费者**模式

### 日志
- 单例模式 
- 异步日志 
- 日志分级
- 在[config.h](https://github.com/dhcpack/WebServer/blob/main/config/config.h)文件中可以设置是否输出日志、是否输出DEBUG级别日志等。
- 日志文件名称：`YYYY-MM-DD HH-MM-SS.log`
- 日志格式：
```log
  #Software: YL's Webserver version 1.0
  #Date: 2023-05-19 22:01:09
  #Fields: date time [level] client-ip client-method query-url server-port status response-size
  2023-05-19 22:01:09.218833 [INFO] : ========== Server start ==========
  2023-05-19 22:01:51.363809 [INFO] : 106.39.42.245:17626  GET / HTTP/1.1 200 3277
  2023-05-19 22:01:51.385651 [INFO] : 106.39.42.245:17626  GET /css/bootstrap.min.css HTTP/1.1 200 121392
  2023-05-19 22:01:51.386404 [INFO] : 106.39.42.245:17882  GET /css/animate.css HTTP/1.1 200 76206
  2023-05-19 22:01:51.396808 [INFO] : 106.39.42.245:18394  GET /css/font-awesome.min.css HTTP/1.1 200 27522
  2023-05-19 22:01:51.398214 [INFO] : 106.39.42.245:18138  GET /css/magnific-popup.css HTTP/1.1 200 7427
  2023-05-19 22:01:51.400618 [INFO] : 106.39.42.245:18650  GET /css/style.css HTTP/1.1 200 9932
  2023-05-19 22:01:51.401761 [INFO] : 106.39.42.245:18906  GET /js/jquery.js HTTP/1.1 200 85794
  2023-05-19 22:01:51.411294 [INFO] : 106.39.42.245:18138  GET /js/bootstrap.min.js HTTP/1.1 200 37007
  2023-05-19 22:01:51.417860 [INFO] : 106.39.42.245:18650  GET /js/smoothscroll.js HTTP/1.1 200 4639
  2023-05-19 22:01:51.426029 [INFO] : 106.39.42.245:18394  GET /js/jquery.magnific-popup.min.js HTTP/1.1 200 21068
  2023-05-19 22:01:51.429589 [INFO] : 106.39.42.245:18650  GET /js/magnific-popup-options.js HTTP/1.1 200 1233
  2023-05-19 22:01:51.444777 [INFO] : 106.39.42.245:18138  GET /js/wow.min.js HTTP/1.1 200 7215
```