# 基础镜像
FROM ubuntu:latest

# 安装所需的软件包和工具
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    cmake \
    libmysqlclient-dev

# 设置工作目录
WORKDIR /app

# 将项目文件复制到镜像中
COPY . /app

# 构建项目
RUN cmake -S . -B build
RUN cmake --build build

# 定义容器启动时执行的命令
CMD ["./build/WebServer"]
