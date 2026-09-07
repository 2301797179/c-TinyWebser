#include <iostream>
#include <string>
// #include "spdlog/spdlog.h"

// #include "http.h"
#define SPDLOG_HEADER_ONLY

struct http_mapp
{
    // std::unorder_map ;
    std::string action;
    std::string resource;
    std::string protocal;
    std::string url;
    std::string content;
    std::string content_length;

    /* data */
};
http_mapp read_http(std::string http_case)
{
    http_mapp hp;
    auto line_pox = http_case.find("\r\n");
    // spdlog::info("显示line_锚点 {}", line_pox);
    std::cout << line_pox << std::endl;
    auto line = http_case.substr(0, 4);

    for (auto line : http_case)
    {
        // spdlog::info("traverse line {}", line);
    }
    // spdlog::info("traverse line {}", )
    return hp;
};