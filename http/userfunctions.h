//
// Created by ylhappy on 2023/5/4.
//

#ifndef WEBSERVER_USERFUNCTIONS_H
#define WEBSERVER_USERFUNCTIONS_H

#include <string>
#include <unordered_map>
#include <functional>

#include "../mysqlpool/mysqlpool.h"
#include "httputils.h"

/*
 * [GET] USER DEFINED FUNCS
 * */
ResponseMessage get_index(const std::string &url);

ResponseMessage get_welcome(const std::string &url);

ResponseMessage get_video(const std::string &url);

ResponseMessage get_picture(const std::string &url);

ResponseMessage get_register(const std::string &url);

ResponseMessage get_login(const std::string &url);

/*
 * [POST] USER DEFINED FUNCS
 * */
ResponseMessage post_register(const std::unordered_map<std::string, std::string> &post);

ResponseMessage post_login(const std::unordered_map<std::string, std::string> &post);

class UserFunc {
public:
    /*
     * USER DEFINED FUNCS
     * */
    /*  GET请求对应的视图函数  */
    static std::unordered_map<std::string, std::function<ResponseMessage(std::string)>> GET_FUNC;
    /*  POST请求对应的视图函数  */
    static std::unordered_map<std::string,
            std::function<ResponseMessage(std::unordered_map<std::string, std::string>)>> POST_FUNC;
};


#endif //WEBSERVER_USERFUNCTIONS_H
