//
// Created by ylhappy on 2023/5/3.
//

#include "httprequest.h"

using namespace std;

/*
 * 初始化类的静态变量
 * */
bool HttpRequest::htmlLoaded_ = false;
/*  GET请求对应的视图函数  */
std::unordered_map<std::string, std::function<std::string(std::string)>> HttpRequest::GET_FUNC{};
/*  POST请求对应的视图函数  */
std::unordered_map<std::string, std::function<std::string(
        std::unordered_map<std::string, std::string>)>> HttpRequest::POST_FUNC{};


HttpRequest::HttpRequest() {
    method_ = path_ = version_ = body_ = "";
    state_ = REQUEST_LINE;
    headers_.clear();
    post_.clear();

    if (!htmlLoaded_) {
        loadHtml();
        htmlLoaded_ = true;
    }
}

void HttpRequest::loadHtml() {
    // load GET_FUNC
    GET_FUNC["/index"] = get_index, GET_FUNC["/welcome"] = get_welcome, GET_FUNC["/video"] = get_video;
    GET_FUNC["/picture"] = get_picture, GET_FUNC["/register"] = get_register, GET_FUNC["/login"] = get_login;

    // load POST_FUNC
    POST_FUNC["/login"] = post_login, POST_FUNC["/register"] = post_register;
}

// 主状态机
bool HttpRequest::parse(Buffer &buff) {
    const char CRLF[] = "\r\n";  // HTML换行
    if (buff.ReadableBytes() <= 0) {
        return false;
    }
    while (buff.ReadableBytes() && state_ != FINISH) {
        const char *lineEnd = search(buff.Peek(), buff.BeginWriteConst(), CRLF, CRLF + 2);
        std::string line(buff.Peek(), lineEnd);
        switch (state_) {
            case REQUEST_LINE:
                if (!parseRequestLine_(line)) return false;
                break;
            case HEADERS:
                parseHeaders_(line);
                if (buff.ReadableBytes() <= 2) {
                    state_ = FINISH;
                }
                break;
            case BODY:
                parseBody_(line);
                break;
            default:
                break;
        }
        if (lineEnd == buff.BeginWrite()) break;
        buff.RetrieveUntil(lineEnd + 2);
    }
    string keepalive = isKeepAlive() ? "true" : "false";
    LOG_INFO("HttpRequest Parsed! Method: %s, Path: %s, Version: %s, KeepAlive: %s\n",
             method_.c_str(), path_.c_str(), version_.c_str(), keepalive.c_str());
    getReturnHtml_();
    LOG_INFO("Result Html generated!\n");
    return true;
}

bool HttpRequest::parseRequestLine_(const string &line) {
    regex patten("^([^ ]*) ([^ ]*) HTTP/([^ ]*)$");
    smatch subMatch;
    if (regex_match(line, subMatch, patten)) {
        method_ = subMatch[1];
        path_ = subMatch[2];
        version_ = subMatch[3];
        state_ = HEADERS;
        return true;
    }
    LOG_ERROR("RequestLine Parse Error.");
    return false;
}

void HttpRequest::getReturnHtml_() {
    if (path_ == "/") {  // default html
        path_ = "/index.html";
    } else if (method_ == "GET") {
        if (GET_FUNC.count(path_)) path_ = GET_FUNC[path_](path_);
        else path_ = "/404.html";
    } else if (method_ == "POST") {
        if (POST_FUNC.count(path_)) path_ = POST_FUNC[path_](post_);
        else path_ = "/404.html";
    } else {
        path_ = "404.html";
    }
}

void HttpRequest::parseHeaders_(const string &line) {
    regex patten("^([^:]*): ?(.*)$");
    smatch subMatch;
    if (regex_match(line, subMatch, patten)) {
        headers_[subMatch[1]] = subMatch[2];
    } else {
        state_ = BODY;
    }
}

void HttpRequest::parseBody_(const string &line) {
    // 解析POST请求的请求体，通常的GET请求没有请求体
    body_ = line;
    parsePost_();
    state_ = FINISH;
}


bool HttpRequest::isKeepAlive() const {
    if (headers_.count("Connection")) {
        return headers_.find("Connection")->second == "keep-alive" && version_ == "1.1";
    }
    return false;
}

void HttpRequest::parsePost_() {
    if (method_ != "POST") return;
    if (headers_["Content-Type"] == "application/x-www-form-urlencoded") parseUrlencoded();
    else {
        LOG_ERROR("Content-Type not Supported.\n");
        return;
    }
}

void HttpRequest::parseUrlencoded() {
    std::stringstream ss(body_);
    std::string pair;
    while (std::getline(ss, pair, '&')) {
        std::string key, value;
        std::stringstream ss_pair(pair);
        if (std::getline(ss_pair, key, '=') && std::getline(ss_pair, value)) {
            // Replace '+' with ' ' and decode percent-encoded characters
            for (std::size_t i = 0; i < value.size(); ++i) {
                if (value[i] == '+') {
                    value[i] = ' ';
                } else if (value[i] == '%' && i + 2 < value.size()) {
                    std::string hex = value.substr(i + 1, 2);
                    int code = std::stoi(hex, nullptr, 16);
                    value.replace(i, 3, 1, static_cast<char>(code));
                }
            }
            post_[key] = value;
            LOG_DEBUG("Parse application/x-www-form-urlencoded:: (%s: %s)", key.c_str(), value.c_str());
        }
    }
}

std::string HttpRequest::path() const {
    return path_;
}

std::string &HttpRequest::path() {
    return path_;
}

std::string HttpRequest::method() const {
    return method_;
}

std::string HttpRequest::version() const {
    return version_;
}

std::string HttpRequest::getPost(const std::string &key) const {
    if (post_.count(key) == 1) {
        return post_.find(key)->second;
    }
    return "";
}

std::string HttpRequest::getPost(const char *key) const {
    if (post_.count(key) == 1) {
        return post_.find(key)->second;
    }
    return "";
}

