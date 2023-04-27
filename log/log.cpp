//
// Created by ylhappy on 2023/4/25.
//
#include "log.h"
#include <iostream>

Log::~Log() {
    if (writeThread_ && writeThread_->joinable()) {
        while (!blockQueue_->empty()) {
            blockQueue_->flush();
        }
        blockQueue_->close();
        writeThread_->join();
    }
    if (file_stream_.is_open()) {
        std::lock_guard<std::mutex> lockGuard(mutex_);
        file_stream_.flush();
        file_stream_.close();
    }
}

void Log::new_file(std::tm tm) {
    // 拼接日志名称
    char fileName[MAX_LOG_NAME_LEN] = {0};
    snprintf(fileName, MAX_LOG_NAME_LEN - 1, "./%04d_%02d_%02d_%02d_%02d_%02d.log",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // 打开文件
    file_stream_ = std::ofstream(fileName);
}


void Log::init(uint32_t queueCapacity) {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    isOpen_ = true;
    total_lines_ = 0;

    // 新建文件流、队列和线程
    new_file(tm);
    blockQueue_.reset(new BlockQueue<std::string>(queueCapacity));
    writeThread_.reset(new std::thread(async_write_thread));
}

Log &Log::instance() {
    static Log instance;
    return instance;
}

void Log::async_write_log() {
    std::string curr_log;
    while (blockQueue_->pop(curr_log)) {
        std::lock_guard<std::mutex> lockGuard(mutex_);
        if (total_lines_ != 0 && total_lines_ % MAX_LOG_NAME_LEN == 0) {  // 写满一个文件
            auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            std::tm tm = *std::localtime(&t);

            file_stream_.flush();
            file_stream_.close();
            new_file(tm);
        }
        total_lines_++;
        printf("total lines: %d, currlog = %s\n", total_lines_, curr_log.c_str());
        file_stream_ << curr_log;
    }
}

void Log::async_write_thread() {
    instance().async_write_log();
}

void Log::write_log(Level level, const char *format, ...) {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&t);

    std::unique_lock<std::mutex> uniqueLock(mutex_);

    int n = snprintf(buff_.BeginWrite(), 128, "%d-%02d-%02d %02d:%02d:%02d.%06ld ",
                     tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec,
                     std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count());
    buff_.HasWritten(n);

    std::string tag;
    if (level == Level::DEBUG) tag = "[DEBUG]: ";
    else if (level == Level::INFO) tag = "[INFO] : ";
    else if (level == Level::WARNING) tag = "[WARN] : ";
    else if (level == Level::ERROR) tag = "[ERROR]: ";
    else if (level == Level::FATAL) tag = "[FATAL]: ";
    buff_.Append(tag);

    va_list vaList;
    va_start(vaList, format);
    int m = vsnprintf(buff_.BeginWrite(), buff_.WritableBytes(), format, vaList);
    va_end(vaList);

    buff_.HasWritten(m);
    buff_.Append("\r\n", 1);
    if (blockQueue_ && !blockQueue_->full()) blockQueue_->push_back(buff_.RetrieveAllToStr());

    buff_.RetrieveAll();
}

//void Log::flush() {
//    blockQueue_->flush();
//    writeThread_->join();
//    file_stream_.flush();
//}






