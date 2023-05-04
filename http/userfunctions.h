//
// Created by ylhappy on 2023/5/4.
//

#ifndef WEBSERVER_USERFUNCTIONS_H
#define WEBSERVER_USERFUNCTIONS_H

#include <string>
#include <unordered_map>

#include "../mysqlpool/mysqlpool.h"

/*
 * [GET] USER DEFINED FUNCS
 * */
std::string get_index(const std::string& url);

std::string get_welcome(const std::string& url);

std::string get_video(const std::string& url);

std::string get_picture(const std::string& url);

std::string get_register(const std::string& url);

std::string get_login(const std::string& url);

/*
 * [POST] USER DEFINED FUNCS
 * */
std::string post_register(const std::unordered_map<std::string, std::string>& post);

std::string post_login(const std::unordered_map<std::string, std::string>& post);


#endif //WEBSERVER_USERFUNCTIONS_H
