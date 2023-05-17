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
    DEBUG, INFO, WARN, ERROR, FATAL
};

class Log {
public:
    /*
     * init must be called first!!!
     * */
    bool init(uint32_t queueCapacity = 1024);

    static Log &instance();

    bool new_file(std::tm tm);

    void write_log(Level level, const char *format, ...);

    bool isOpen() const;

    void flush();

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

    bool isOpen_ = false;
    uint64_t total_lines_;
    Buffer buff_;
    std::ofstream file_stream_;
    std::unique_ptr<BlockQueue<std::string>> blockQueue_;
    std::unique_ptr<std::thread> writeThread_;
    std::mutex mutex_;

    static void async_write_thread();
};


template<typename... Args>
void LOG_BASE(const Level level, const char *format, Args... args) {
    Log &log = Log::instance();
    if (log.isOpen()) {
        log.write_log(level, format, args...);
        log.flush();
    }

}

template<typename... Args>
void LOG_DEBUG(const char *format, Args... args) {
    LOG_BASE(Level::DEBUG, format, args...);
}

template<typename... Args>
void LOG_INFO(const char *format, Args... args) {
    LOG_BASE(Level::INFO, format, args...);
}

template<typename... Args>
void LOG_WARN(const char *format, Args... args) {
    LOG_BASE(Level::WARN, format, args...);
}

template<typename... Args>
void LOG_ERROR(const char *format, Args... args) {
    LOG_BASE(Level::ERROR, format, args...);
}

template<typename... Args>
void LOG_FATAL(const char *format, Args... args) {
    LOG_BASE(Level::FATAL, format, args...);
}

#endif // WEBSERVER_LOG_H
