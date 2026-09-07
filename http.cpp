#include <iostream>
#include <string>
// #include "spdlog/spdlog.h"

#include "http.h"
#define SPDLOG_HEADER_ONLY
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#define SENDFLAG 0
// #include "spdlog/spdlog.h"

void http_request_parser::http_parse(std::string &request) {
};

void http_request_parser::http_request_parser_runner(const char *accepted_request, int client_fd)
{
    accepted_request_parse(accepted_request);
    http_split();

    std::cout << "print" << std::endl;
    std::cout << this->request.request_line.request_line_method << std::endl;

    std::cout << this->request.request_line.request_line_uri << std::endl;
    std::cout << this->request.request_line.request_line_version << std::endl;
    bool flag = this->request.request_line.request_line_method == "GET" && this->request.request_line.request_line_version == "HTTP/1.1\r";
    std::cout << flag << std::endl;
    if (this->request.request_line.request_line_method == "GET" && this->request.request_line.request_line_version == "HTTP/1.1\r")
    {
        send_index_response(client_fd);
        std::cout << "发送成功" << std::endl;
    };
    // send_index_response(client_fd);
    // std::cout << "发送成功" << std::endl;
    // std::cout << "--- [开始遍历 Headers 哈希表] ---" << std::endl;
    // for (const auto &pair : this->request.headers)
    // {
    //     std::cout << "   -> [" << pair.first << "] : " << pair.second << std::endl;
    // }
    // std::cout << "--- [Headers 哈希表遍历结束] ---" << std::endl;
};

void http_request_parser::send_index_response(int client_fd)
{
    std::ifstream file("./html/index.html");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string html_content = "";
    html_content = buffer.str();

    std::string http_response = "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/html; charset=utf-8\r\n"
                                "Content-Length: " +
                                std::to_string(html_content.size()) + "\r\n"
                                                                      "Connection: close\r\n"
                                                                      "\r\n" +
                                html_content;
    send(client_fd, http_response.data(), http_response.size(), SENDFLAG);
}

// template <size_t N>
// void http_request_parser::http_request_parser_runner(const char* accepted_request)
// {
//     accepted_request_parse(accepted_request);
//     http_split();
// };

void http_request_parser::http_split()
{
    // 分割请求行
    while (this->http_parse_state == HTTP_REQUEST_LINE)
    {

        if (this->http_parse_state == HTTP_REQUEST_LINE)
        {
            get_http_request_line_method();
            this->http_parse_state = HTTP_REQUEST_HEADER;
            // 提取出请求头并执行响应
        }
        else if (this->http_parse_state == HTTP_REQUEST_HEADER)
        {
            get_http_request_header_method();
            this->http_parse_state = HTTP_REQUEST_SUCCESS;
        }
        else if (this->http_parse_state == HTTP_REQUEST_BODY)
        {
            this->http_parse_state = HTTP_REQUEST_SUCCESS;
        }
    }
};

void http_request_parser::get_http_request_line_method()
{
    // 解析请求行方法

    int poisx_method = this->accepted_request_parsed.find(" ");
    int poisx_uri = this->accepted_request_parsed.find(" ", poisx_method + 1);
    size_t url_len = poisx_uri - poisx_method - 1;
    int posix_version = this->accepted_request_parsed.find("HTTP/", poisx_method + 1);
    this->request.request_line.request_line_method = this->accepted_request_parsed.substr(0, poisx_method);
    this->request.request_line.request_line_uri = this->accepted_request_parsed.substr(poisx_method + 1, url_len);
    this->request.request_line.request_line_version = this->accepted_request_parsed.substr(posix_version);
};

void http_request_parser::get_http_request_header_method()
{
    // 解析请求头方法
    int start_pos = 0;
    while (start_pos < this->accepted_request_parsed.length())
    {
        int end_pos = this->accepted_request_parsed.find("\r\n", start_pos);
        if (end_pos != std::string::npos)
        {
            auto request_header_line = this->accepted_request_parsed.substr(start_pos, end_pos - start_pos);
        };
        auto request_header_line = this->accepted_request_parsed.substr(start_pos, end_pos - start_pos);
        if (end_pos != std::string::npos)
        {
            int request_header_line_poisx = request_header_line.find(": ", 0);
            auto request_header_line_key = request_header_line.substr(0, request_header_line_poisx - 0);
            auto request_header_line_value = request_header_line.substr(request_header_line_poisx + 2);
            this->request.headers[request_header_line_key] = request_header_line_value;
        }
        start_pos = end_pos + 2;
        if (end_pos == std::string::npos)
        {
            start_pos = this->accepted_request_parsed.length();
        }
    };
};

// struct http_mapp
// {
//     // std::unorder_map ;
//     std::string action;
//     std::string resource;
//     std::string protocal;
//     std::string url;
//     std::string content;
//     std::string content_length;

//     /* data */
// };

// http_mapp read_http(std::string http_case)
// {
//     http_mapp hp;
//     auto line_pox = http_case.find("\r\n");
//     // spdlog::info("显示line_锚点 {}", line_pox);
//     std::cout << line_pox << std::endl;
//     auto line = http_case.substr(0, 4);

//     for (auto line : http_case)
//     {
//         // spdlog::info("traverse line {}", line);
//     }
//     // spdlog::info("traverse line {}", )
//     return hp;
// };
// def

// int main()
// {
//     std::string http_case = "POST /login HTTP/1.1\r\n"
//                             "Host: example.com\r\n"
//                             "Content-Type: application/x-www-form-urlencoded\r\n"
//                             "Content-Length: 27\r\n"
//                             "\r\n"
//                             "username=admin&password=123";
//     read_http(http_case);
//     http_request_parser parser;
//     parser.http_split(http_case);
//     spdlog::info("http_case 解析已完成");
// };
// End of file.