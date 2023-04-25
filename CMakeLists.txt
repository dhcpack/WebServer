cmake_minimum_required(VERSION 3.23)
project(WebServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(WebServer main.cpp ./threadpool/threadpool.cpp)
