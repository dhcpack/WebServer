//
// Created by ylhappy on 2023/5/3.
//

#ifndef WEBSERVER_HTTPREQUEST_H
#define WEBSERVER_HTTPREQUEST_H

/*
 * 解析HTTP请求报文
 * 状态机
 *
 * Request Line
 * Headers
 * Content
 * */

#include <unordered_map>
#include <string>
#include <regex>

#include "../buffer/buffer.h"
#include "../log/log.h"
#include "userfunctions.h"

class HttpRequest {
public:
    enum PARSE_STATE {
        REQUEST_LINE,
        HEADERS,
        BODY,
        FINISH,
    };

    enum HTTP_CODE {
        NO_REQUEST = 0,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESOURSE,
        FORBIDDENT_REQUEST,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION,
    };

    HttpRequest();

    ~HttpRequest() = default;

    bool parse(Buffer &buff);

    std::string path() const;

    std::string &path();

    std::string method() const;

    std::string version() const;

    std::string getPost(const std::string &key) const;

    std::string getPost(const char *key) const;

    bool isKeepAlive() const;

    void clear();

private:
    bool parseRequestLine_(const std::string &line);

    void parseHeaders_(const std::string &line);

    void parseBody_(const std::string &line);

    void parsePost_();

    void getReturnHtml_();

    /*
    TODO
        void HttpConn::ParseFormData() {}
        void HttpConn::ParseJson() {}
    */

    void parseUrlencoded();

    PARSE_STATE state_;
    /*  方法，路径，版本号  请求体  */
    std::string method_, path_, version_, body_;
    /*  请求头  */
    std::unordered_map<std::string, std::string> headers_;
    /*  请求体  */
    std::unordered_map<std::string, std::string> post_;


    /*
     * USER DEFINED FUNCS
     * */
    static bool userFuncsLoaded_;
    /*  GET请求对应的视图函数  */
    static std::unordered_map<std::string, std::function<std::string(std::string)>> GET_FUNC;
    /*  POST请求对应的视图函数  */
    static std::unordered_map<std::string,
            std::function<std::string(std::unordered_map<std::string, std::string>)>> POST_FUNC;

    static void loadUserFuncs();
};

#endif //WEBSERVER_HTTPREQUEST_H
