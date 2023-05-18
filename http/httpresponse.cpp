//
// Created by ylhappy on 2023/5/5.
//

#include "httpresponse.h"

/*
 * 初始化类的静态变量
 * */
/*  GET请求对应的视图函数  */
std::unordered_map<std::string, std::function<ResponseMessage(std::string)>> HttpResponse::GET_FUNC{
        {"/index",    get_index},
        {"/welcome",  get_welcome},
        {"/video",    get_video},
        {"/picture",  get_picture},
        {"/register", get_register},
        {"/login",    get_login},
};

/*  POST请求对应的视图函数  */
std::unordered_map<std::string, std::function<ResponseMessage(
        std::unordered_map<std::string, std::string>)>> HttpResponse::POST_FUNC{
        {"/login",    post_login},
        {"/register", post_register},
};

/*  文件后缀名到MIME类型的映射  */
const std::unordered_map<std::string, std::string> HttpResponse::SUFFIX2MIME = {
        {".html",  "text/html"},
        {".xml",   "text/xml"},
        {".xhtml", "application/xhtml+xml"},
        {".txt",   "text/plain"},
        {".rtf",   "application/rtf"},
        {".pdf",   "application/pdf"},
        {".word",  "application/nsword"},
        {".png",   "image/png"},
        {".gif",   "image/gif"},
        {".jpg",   "image/jpeg"},
        {".jpeg",  "image/jpeg"},
        {".au",    "audio/basic"},
        {".mpeg",  "video/mpeg"},
        {".mpg",   "video/mpeg"},
        {".avi",   "video/x-msvideo"},
        {".gz",    "application/x-gzip"},
        {".tar",   "application/x-tar"},
        {".css",   "text/css "},
        {".js",    "text/javascript "},
//        {".mp4",   "video/mp4"},
        {".ico",   "image/x-icon"},
};

const std::unordered_map<HTTP_STATUS_CODE, std::string> HttpResponse::CODE2STATUS = {
        {OK,                    "OK"},
        {CREATED,               "Created"},
        {BAD_REQUEST,           "Bad Request"},
        {FORBIDDEN,             "Forbidden"},
        {NOT_FOUND,             "Not Found"},
        {INTERNAL_SERVER_ERROR, "Internal Server Error"}
};

HttpResponse::HttpResponse() {
    srcDir_ = "";
    isKeepAlive_ = false;
    mmFile_ = nullptr;
    mmFileStat_ = {0};
};

HttpResponse::~HttpResponse() {
    unmapFile();
}

void HttpResponse::init(const std::string &srcDir, bool isKeepAlive, bool isBadRequest, HTTP_METHOD method,
                        std::string &path, std::unordered_map<std::string, std::string> &post) {
    assert(srcDir != "");
    if (mmFile_) { unmapFile(); }
    isKeepAlive_ = isKeepAlive;
    srcDir_ = srcDir;
    mmFile_ = nullptr;
    mmFileStat_ = {0};

    if (isBadRequest) path_ = "/error.html", code_ = HTTP_STATUS_CODE::BAD_REQUEST;
    else if (path == "/") {  // default html
        path_ = "/index.html", code_ = HTTP_STATUS_CODE::OK;
    } else if (method == HTTP_METHOD::GET) {
        if (GET_FUNC.count(path)) {
            ResponseMessage getResponse = GET_FUNC[path](path);
            path_ = getResponse.html_path_.value(), code_ = getResponse.code_;
        } else path_ = path, code_ = HTTP_STATUS_CODE::OK;
    } else if (method == HTTP_METHOD::POST) {
        if (POST_FUNC.count(path)) {
            ResponseMessage postResponse = POST_FUNC[path](post);
            path_ = postResponse.html_path_.value(), code_ = postResponse.code_;
        } else path_ = "/404.html", code_ = HTTP_STATUS_CODE::NOT_FOUND;
    } else path_ = "/404.html", code_ = HTTP_STATUS_CODE::NOT_FOUND;
}

void HttpResponse::makeResponse(Buffer &buff) {
    // 判断请求的文件是否存在
    if (stat((srcDir_ + path_).data(), &mmFileStat_) < 0 || S_ISDIR(mmFileStat_.st_mode)) {  // 请求的文件不存在或是目录
        code_ = HTTP_STATUS_CODE::NOT_FOUND, path_ = "/404.html";
    } else if (!(mmFileStat_.st_mode & S_IROTH)) {  // 请求的文件没有可读权限
        code_ = HTTP_STATUS_CODE::FORBIDDEN, path_ = "/403.html";
    }
    addStateLine_(buff);
    addHeader_(buff);
    addContent_(buff);
}

char *HttpResponse::file() {
    return mmFile_;
}

size_t HttpResponse::fileLen() const {
    return mmFileStat_.st_size;
}

void HttpResponse::addStateLine_(Buffer &buff) {
    std::string status = CODE2STATUS.find(code_)->second;
    buff.Append("HTTP/1.1 " + std::to_string(code_) + " " + status + "\r\n");
}

void HttpResponse::addHeader_(Buffer &buff) {
    buff.Append("Connection: ");
    if (isKeepAlive_) {
        buff.Append("keep-alive\r\n");
        buff.Append("keep-alive: max=6, timeout=120\r\n");
    } else {
        buff.Append("close\r\n");
    }
    buff.Append("Content-type: " + getFileType_() + "\r\n");
}

void HttpResponse::addContent_(Buffer &buff) {
    int srcFd = open((srcDir_ + path_).data(), O_RDONLY);
    if (srcFd < 0) {
        errorContent(buff, "file NotFound!");
        return;
    }

    /* 将文件映射到内存提高文件的访问速度
        MAP_PRIVATE 建立一个写入时拷贝的私有映射*/
    LOG_DEBUG("file path %s\n", (srcDir_ + path_).data());
    void *mmRet = mmap(0, mmFileStat_.st_size, PROT_READ, MAP_PRIVATE, srcFd, 0);
    if (mmRet == MAP_FAILED) {
        errorContent(buff, "file NotFound!");
        return;
    }
    mmFile_ = (char *) mmRet;
    close(srcFd);
    buff.Append("Content-length: " + std::to_string(mmFileStat_.st_size) + "\r\n\r\n");
}

void HttpResponse::unmapFile() {
    if (mmFile_) {
        munmap(mmFile_, mmFileStat_.st_size);
        mmFile_ = nullptr;
    }
}

std::string HttpResponse::getFileType_() {
    /* 判断文件类型 */
    std::string::size_type idx = path_.find_last_of('.');
    if (idx == std::string::npos) {
        return "text/plain";
    }
    std::string suffix = path_.substr(idx);
    if (SUFFIX2MIME.count(suffix) == 1) {
        return SUFFIX2MIME.find(suffix)->second;
    }
    return "text/plain";
}

void HttpResponse::errorContent(Buffer &buff, const std::string &message) {
    std::string body;
    std::string status;
    body += "<html><title>Error</title>";
    body += "<body bgcolor=\"ffffff\">";
    if (CODE2STATUS.count(code_) == 1) {
        status = CODE2STATUS.find(code_)->second;
    } else {
        status = "Bad Request";
    }
    body += std::to_string(code_) + " : " + status + "\n";
    body += "<p>" + message + "</p>";
    body += "<hr><em>Yuelin's WebServer</em></body></html>";

    buff.Append("Content-length: " + std::to_string(body.size()) + "\r\n\r\n");
    buff.Append(body);
}
