//
// Created by ylhappy on 2023/4/25.
//
#include "log.h"

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

bool Log::new_file(std::tm tm) {
    // 拼接日志名称
    char fileName[MAX_LOG_NAME_LEN] = {0};
    snprintf(fileName, MAX_LOG_NAME_LEN - 1, "./%04d-%02d-%02d %02d-%02d-%02d.log",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    // 打开文件
    file_stream_ = std::ofstream(fileName);
    if (!file_stream_.is_open()) return false;

    // log头
    char log_date[25];
    snprintf(log_date, 25, "%04d-%02d-%02d %02d:%02d:%02d",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    file_stream_ << "#Software: YL's Webserver version 1.0\n"
                    "#Date: " << log_date << "\n" <<
                 "#Fields: date time client-ip client-method query-url server-port status response-size\n";
    file_stream_.flush();
    return true;
}


bool Log::init(uint32_t queueCapacity) {
    struct timeval now = {0, 0};
    gettimeofday(&now, nullptr);
    time_t t = now.tv_sec;
    std::tm tm = *localtime(&t);

    isOpen_ = true;
    total_lines_ = 0;

    // 新建文件流、队列和线程
    if (!new_file(tm)) return false;
    blockQueue_.reset(new BlockQueue<std::string>(queueCapacity));
    writeThread_.reset(new std::thread(async_write_thread));
    return true;
}

Log &Log::instance() {
    static Log instance;
    return instance;
}

void Log::async_write_log() {
    std::string curr_log;
    while (blockQueue_->pop(curr_log)) {
        std::lock_guard<std::mutex> lockGuard(mutex_);
        file_stream_ << curr_log;
    }
}

void Log::async_write_thread() {
    instance().async_write_log();
}

void Log::write_log(Level level, const char *format, ...) {
    struct timeval now = {0, 0};
    gettimeofday(&now, nullptr);
    time_t t = now.tv_sec;
    std::tm tm = *localtime(&t);

    std::unique_lock<std::mutex> uniqueLock(mutex_);
    if (total_lines_ != 0 && total_lines_ % MAX_FILE_LINE == 0) {  // 写满一个文件
        file_stream_.flush();
        file_stream_.close();
        new_file(tm);  // 新建文件
    }

    total_lines_++;
    int n = snprintf(buff_.BeginWrite(), 128, "%d-%02d-%02d %02d:%02d:%02d.%06ld ",
                     tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, now.tv_usec);
    buff_.HasWritten(n);

    std::string tag;
    if (level == Level::DEBUG) tag = "[DEBUG]: ";
    else if (level == Level::INFO) tag = "[INFO] : ";
    else if (level == Level::WARN) tag = "[WARN] : ";
    else if (level == Level::ERROR) tag = "[ERROR]: ";
    else if (level == Level::FATAL) tag = "[FATAL]: ";
    buff_.Append(tag);

    va_list vaList;
    va_start(vaList, format);
    int m = vsnprintf(buff_.BeginWrite(), buff_.WritableBytes(), format, vaList);
    va_end(vaList);
    buff_.HasWritten(m);

//    buff_.Append("\r\n", 1);
    if (blockQueue_ && !blockQueue_->full()) blockQueue_->push_back(buff_.RetrieveAllToStr());

    buff_.RetrieveAll();
}

bool Log::isOpen() const {
    return isOpen_;
}

void Log::flush() {
    while (!blockQueue_->empty()) {
        blockQueue_->flush();
    }
//    blockQueue_->flush();
//    writeThread_->join();
    file_stream_.flush();
}






