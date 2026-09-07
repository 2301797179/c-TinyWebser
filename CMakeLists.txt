# 1. 声明 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.14)

# 2. 定义您的项目名称
project(HttpServer LANGUAGES CXX)

# 3. 强制要求使用 C++17 标准（处理 string 等高级特性需要）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 在系统中寻找已经安装的 spdlog 库
find_package(spdlog REQUIRED)

# 5. 告诉 CMake：我要编译一个叫 http_server 的程序，源码是 http.cpp
add_executable(http_server http.cpp)

# 6. 核心：让 http_server 程序链接 spdlog 库
# 它会自动帮您搞定上一节报错的那个 -lspdlog 和 -lfmt 链接参数
target_link_libraries(http_server PRIVATE spdlog::spdlog)
