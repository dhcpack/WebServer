cmake_minimum_required(VERSION 3.23)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(WebServer main.cpp ./log/log.cpp ./buffer/buffer.cpp ./mysqlpool/mysqlpool.cpp ./timer/heaptimer.cpp
        ./http/httprequest.cpp ./http/userfunctions.cpp ./http/httpresponse.cpp)

target_link_libraries(${PROJECT_NAME} pthread mysqlclient)
