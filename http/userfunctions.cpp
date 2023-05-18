//
// Created by ylhappy on 2023/5/4.
//
#include "userfunctions.h"

/*
 * [GET] USER DEFINED FUNCS
 * */
ResponseMessage get_index(const std::string &url) {
    return {"/index.html", HTTP_STATUS_CODE::OK};
}

ResponseMessage get_welcome(const std::string &url) {
    return {"/welcome.html", HTTP_STATUS_CODE::OK};
}

ResponseMessage get_video(const std::string &url) {
    return {"/video.html", HTTP_STATUS_CODE::OK};
}

ResponseMessage get_picture(const std::string &url) {
    return {"/picture.html", HTTP_STATUS_CODE::OK};
}

ResponseMessage get_register(const std::string &url) {
    return {"/register.html", HTTP_STATUS_CODE::OK};
}

ResponseMessage get_login(const std::string &url) {
    return {"/login.html", HTTP_STATUS_CODE::OK};
}

/*
 * [POST] USER DEFINED FUNCS
 * */
ResponseMessage post_register(const std::unordered_map<std::string, std::string> &post) {
    if (!post.count("username") || !post.count("password")) {
        return {"/error.html", HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR};
    }
    const std::string &username = post.find("username")->second, &password = post.find("password")->second;
    LOG_DEBUG("Register with username = %s, password = %s\n", username.c_str(), password.c_str());
    MYSQL *sql;
    MySqlManager manager(&sql);

    // Construct the query to retrieve the user's information
    char query[256] = {0};
    snprintf(query, 256, "SELECT username, password FROM user WHERE username='%s' LIMIT 1", username.c_str());
    LOG_DEBUG("MySql query: %s\n", query);

    // Execute the query
    if (mysql_query(sql, query)) {
        LOG_ERROR("MySql query error: %s\n", mysql_error(sql));
        return {"/error.html", HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR};
    }

    // Retrieve the results of the query
    MYSQL_RES *res = mysql_store_result(sql);
    if (!res) {
        LOG_ERROR("MySql retrieve error: %s\n", mysql_error(sql));
        return {"/error.html", HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR};
    }

    // Get the number of rows returned
    uint64_t num_rows = mysql_num_rows(res);
    if (num_rows != 0) {
        LOG_DEBUG("User %s already exist.\n", username.c_str());
        mysql_free_result(res);
        return {"/403.html", HTTP_STATUS_CODE::FORBIDDEN};
    }

    snprintf(query, 256, "insert into user(username, password) values('%s', '%s')", username.c_str(), password.c_str());
    LOG_DEBUG("MySql insert: %s\n", query);

    // Execute the insert
    if (mysql_query(sql, query)) {
        LOG_ERROR("MySql insert error: %s\n", mysql_error(sql));
        return {"/error.html", HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR};
    }
    LOG_DEBUG("User %s, password %s register succeed!\n", username.c_str(), password.c_str());
    return {"/login.html", HTTP_STATUS_CODE::CREATED};


}

ResponseMessage post_login(const std::unordered_map<std::string, std::string> &post) {
    if (!post.count("username") || !post.count("password")) {
        return {"/error.html", HTTP_STATUS_CODE::INTERNAL_SERVER_ERROR};
    }
    const std::string &username = post.find("username")->second, &password = post.find("password")->second;
    LOG_DEBUG("Login with username = %s, password = %s\n", username.c_str(), password.c_str());
    MYSQL *sql;
    MySqlManager manager(&sql);

    // Construct the query to retrieve the user's information
    char query[256] = {0};
    snprintf(query, 256, "SELECT username, password FROM user WHERE username='%s' LIMIT 1", username.c_str());
    LOG_DEBUG("MySql query: %s\n", query);

    // Execute the query
    if (mysql_query(sql, query)) {
        LOG_ERROR("MySql query error: %s\n", mysql_error(sql));
        return {"/error.html", INTERNAL_SERVER_ERROR};
    }

    // Retrieve the results of the query
    MYSQL_RES *res = mysql_store_result(sql);
    if (!res) {
        LOG_ERROR("MySql retrieve error: %s\n", mysql_error(sql));
        return {"/error.html", INTERNAL_SERVER_ERROR};
    }

    // Get the number of rows returned
    uint64_t num_rows = mysql_num_rows(res);
    if (num_rows == 0) {
        LOG_DEBUG("User %s not found.\n", username.c_str());
        mysql_free_result(res);
        return {"/404.html", HTTP_STATUS_CODE::NOT_FOUND};
    }

    // Get the user's information
    MYSQL_ROW row = mysql_fetch_row(res);
    std::string db_username = row[0];
    std::string db_password = row[1];
    mysql_free_result(res);

    // Check the password
    if (password == db_password) {
        LOG_DEBUG("User %s login succeed!\n", username.c_str());
        return {"/welcome.html", HTTP_STATUS_CODE::OK};
    } else {
        LOG_DEBUG("Wrong password.\n");
        return {"/403.html", HTTP_STATUS_CODE::FORBIDDEN};
    }
}
