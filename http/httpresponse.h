//
// Created by ylhappy on 2023/5/5.
//

#ifndef WEBSERVER_HTTPRESPONSE_H
#define WEBSERVER_HTTPRESPONSE_H

#include <unordered_map>
#include <fcntl.h>       // open
#include <unistd.h>      // close_
#include <sys/stat.h>    // stat
#include <sys/mman.h>    // mmap, munmap
#include <functional>

#include "../buffer/buffer.h"
#include "../log/log.h"
#include "userfunctions.h"

class HttpResponse {
public:
    HttpResponse();

    ~HttpResponse();

    void init(const std::string &srcDir, bool isKeepAlive, bool isBadRequest, HTTP_METHOD method, std::string &path,
              std::unordered_map<std::string, std::string> &post);

    void makeResponse(Buffer &buff);

    void unmapFile();

    char *file();

    size_t fileLen() const;

    void errorContent(Buffer &buff, const std::string& message);

    int code() const { return code_; }

private:
    void addStateLine_(Buffer &buff);

    void addHeader_(Buffer &buff);

    void addContent_(Buffer &buff);

    std::string getFileType_();

    HTTP_STATUS_CODE code_{};
    bool isKeepAlive_;

    std::string path_;
    std::string srcDir_;

    char *mmFile_;
    struct stat mmFileStat_{};

    static const std::unordered_map<std::string, std::string> SUFFIX2MIME;
    static const std::unordered_map<HTTP_STATUS_CODE, std::string> CODE2STATUS;

    /*
     * USER DEFINED FUNCS
     * */
    /*  GET请求对应的视图函数  */
    static std::unordered_map<std::string, std::function<ResponseMessage(std::string)>> GET_FUNC;
    /*  POST请求对应的视图函数  */
    static std::unordered_map<std::string,
            std::function<ResponseMessage(std::unordered_map<std::string, std::string>)>> POST_FUNC;
};

#endif //WEBSERVER_HTTPRESPONSE_H
