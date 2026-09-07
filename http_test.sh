# 注意：最后面的 -lspdlog -lfmt 非常重要
g++ -std=c++17 http.cpp -o http_server -lspdlog -lfmt
