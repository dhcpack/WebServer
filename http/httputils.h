//
// Created by ylhappy on 2023/5/17.
//

#ifndef WEBSERVER_HTTPUTILS_H
#define WEBSERVER_HTTPUTILS_H

#include <optional>

enum HTTP_STATUS_CODE {
    OK = 200,
    CREATED = 201,

    BAD_REQUEST = 400,
    FORBIDDEN = 403,
    NOT_FOUND = 404,

    INTERNAL_SERVER_ERROR = 500,
};

struct ResponseMessage {
    std::optional<std::string> html_path_;
    HTTP_STATUS_CODE code_;
};

enum HTTP_METHOD {
    NONE,
    GET, POST, PUT, DELETE,
};
#endif //WEBSERVER_HTTPUTILS_H
