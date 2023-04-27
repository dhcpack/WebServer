//
// Created by ylhappy on 2023/4/25.
//

#ifndef WEBSERVER_LOG_H
#define WEBSERVER_LOG_H

/*
 * 单例模式
 * 异步日志
 * 日志分级
 * */

#include <string>
#include <mutex>
#include <thread>
#include <fstream>

#include <sys/stat.h>
#include <sys/time.h>
#include <cstdarg>

#include "blockqueue.h"
#include "../buffer/buffer.h"

enum class Level {
    DEBUG, INFO, WARNING, ERROR, FATAL
};

class Log {
public:
    /*
     * init must be called first!!!
     * */
    void init(uint32_t queueCapacity = 1024);

    static Log &instance();

    void new_file(std::tm tm, long usec);

    void write_log(Level level, const char *format, ...);

    // For Singleton
    // 删除拷贝构造函数
    Log(const Log &) = delete;

    // 删除拷贝赋值函数
    Log operator=(const Log &) = delete;


private:
    void async_write_log();

    // For Singleton
    Log() = default;

    ~Log();

    static const uint64_t MAX_FILE_LINE = 50000;
    static const uint64_t MAX_LOG_NAME_LEN = 128;

    bool isOpen_;
    uint64_t total_lines_;
    Buffer buff_;
    std::ofstream file_stream_;
    std::unique_ptr<BlockQueue<std::string>> blockQueue_;
    std::unique_ptr<std::thread> writeThread_;
    std::mutex mutex_;

    static void async_write_thread();
};


#endif // WEBSERVER_LOG_H
