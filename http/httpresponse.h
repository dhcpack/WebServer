//
// Created by ylhappy on 2023/5/5.
//

#ifndef WEBSERVER_HTTPRESPONSE_H
#define WEBSERVER_HTTPRESPONSE_H

#include <unordered_map>
#include <fcntl.h>       // open
#include <unistd.h>      // close
#include <sys/stat.h>    // stat
#include <sys/mman.h>    // mmap, munmap

#include "../buffer/buffer.h"
#include "../log/log.h"

class HttpResponse {
public:
    HttpResponse();

    ~HttpResponse();

    void init(const std::string &srcDir, std::string &path, bool isKeepAlive = false, int code = -1);

    void makeResponse(Buffer &buff);

    void unmapFile();

    char *file();

    size_t fileLen() const;

    void errorContent(Buffer &buff, std::string message);

    int code() const { return code_; }

private:
    void addStateLine_(Buffer &buff);

    void addHeader_(Buffer &buff);

    void addContent_(Buffer &buff);

    void errorHtml_();

    std::string getFileType_();

    int code_;
    bool isKeepAlive_;

    std::string path_;
    std::string srcDir_;

    char *mmFile_;
    struct stat mmFileStat_;

    static const std::unordered_map<std::string, std::string> SUFFIX_TYPE;
    static const std::unordered_map<int, std::string> CODE_STATUS;
    static const std::unordered_map<int, std::string> CODE_PATH;
};

#endif //WEBSERVER_HTTPRESPONSE_H
