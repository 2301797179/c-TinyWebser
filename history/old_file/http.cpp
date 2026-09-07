#include <iostream>
#include <string>
# include "spdlog/spdlog.h"

#include "http.h"
void http_request_parser::http_parse(std::string& request) {
};

template<size_t N>
void http_request_parser::http_request_parser_runner(char (&accepted_request)[N]) {
    accepted_request_parse(accepted_request);
    http_split();


};
// void http_request_parser::http_split(std::string& request) {
//     // 分割请求行
//     int posix_request_line = request.find("\r\n");
//     int test = request.find("\r");
//     // std::cout << posix << std::endl
//     auto request_line = request.substr(0, posix_request_line);
//     get_http_request_line_method(request_line);
//     // spdlog::info("request_line已经分割成功 {}", this->request.request_line);
//     spdlog::info("request_line已经分割成功");
//     //分割请求头
//     int posix_request_header = request.find("\r\n\r\n", posix_request_line + 1);
//     size_t request_header_len = posix_request_header - posix_request_line +2;
//     auto request_header = request.substr(posix_request_line + 2, request_header_len - 4);
//     get_http_request_header_method(request_header);
//     std::cout << "显示" << std::endl;
//     // spdlog::info("request_header已经分割成功{}", this->request.headers);
//     spdlog::info("request_header已经分割成功");
//     // std::string breaker = "breaker";
//     // std::cout << this->request << std::endl;
//     // spdlog::info("请求行信息 {}", request_line);
   
// };
void http_request_parser::http_split() {
    // 分割请求行
    if (this->http_parse_state == HTTP_REQUEST_LINE){
        get_http_request_line_method();
        //提取出请求头并执行响应
    }
    else if(this->http_parse_state == HTTP_REQUEST_HEADER){
        get_http_request_header_method();
    }
    
   
};


// void http_request_parser::get_http_request_line_method(std::string& request_line) {
//     // 解析请求行方法
//     int poisx_method = request_line.find(" ");
//     int poisx_uri = request_line.find(" ", poisx_method + 1);
//     size_t url_len = poisx_uri - poisx_method - 1;
//     int posix_version = request_line.find("HTTP/", poisx_method + 1);
//     this->request.request_line.request_line_method = request_line.substr(0, poisx_method);
//     this->request.request_line.request_line_uri = request_line.substr(poisx_method + 1, url_len);
//     this->request.request_line.request_line_version = request_line.substr(posix_version);
// };

void http_request_parser::get_http_request_line_method() {
    // 解析请求行方法
    
    int poisx_method = this->accepted_request_parsed.find(" ");
    int poisx_uri = this->accepted_request_parsed.find(" ", poisx_method + 1);
    size_t url_len = poisx_uri - poisx_method - 1;
    int posix_version = this->accepted_request_parsed.find("HTTP/", poisx_method + 1);
    this->request.request_line.request_line_method = this->accepted_request_parsed.substr(0, poisx_method);
    this->request.request_line.request_line_uri = this->accepted_request_parsed.substr(poisx_method + 1, url_len);
    this->request.request_line.request_line_version = this->accepted_request_parsed.substr(posix_version);
};

// void http_request_parser::get_http_request_header_method(std::string& request_header) {
//     //解析请求头方法
//     int start_pos = 0;
//     while (start_pos < request_header.length()) {
//         int end_pos = request_header.find("\r\n", start_pos);
//         if (end_pos != std::string::npos) {
//             auto request_header_line = request_header.substr(start_pos, end_pos - start_pos);
//         };
//         auto request_header_line = request_header.substr(start_pos, end_pos - start_pos);
//         if (end_pos != std::string::npos) {
//         int request_header_line_poisx = request_header_line.find(": ", 0);
//         auto request_header_line_key = request_header_line.substr(0, request_header_line_poisx - 0);
//         auto request_header_line_value = request_header_line.substr(request_header_line_poisx + 2);
//         this->request.headers[request_header_line_key] = request_header_line_value;
//         }
//         // int request_header_line_poisx = request_header_line.find(": ", 0);
//         // auto request_header_line_key = request_header_line.substr(0, request_header_line_poisx - 0);
//         // auto request_header_line_value = request_header_line.substr(request_header_line_poisx + 2);
//         // this->request.headers[request_header_line_key] = request_header_line_value;
//         start_pos = end_pos  + 2;
//         if (end_pos == std::string::npos) {
//             start_pos = request_header.length();
//         }
//     };
// };

void http_request_parser::get_http_request_header_method() {
    //解析请求头方法
    int start_pos = 0;
    while (start_pos < this->accepted_request_parsed.length()) {
        int end_pos = this->accepted_request_parsed.find("\r\n", start_pos);
        if (end_pos != std::string::npos) {
            auto request_header_line = this->accepted_request_parsed.substr(start_pos, end_pos - start_pos);
        };
        auto request_header_line = this->accepted_request_parsed.substr(start_pos, end_pos - start_pos);
        if (end_pos != std::string::npos) {
        int request_header_line_poisx = request_header_line.find(": ", 0);
        auto request_header_line_key = request_header_line.substr(0, request_header_line_poisx - 0);
        auto request_header_line_value = request_header_line.substr(request_header_line_poisx + 2);
        this->request.headers[request_header_line_key] = request_header_line_value;
        }
        // int request_header_line_poisx = request_header_line.find(": ", 0);
        // auto request_header_line_key = request_header_line.substr(0, request_header_line_poisx - 0);
        // auto request_header_line_value = request_header_line.substr(request_header_line_poisx + 2);
        // this->request.headers[request_header_line_key] = request_header_line_value;
        start_pos = end_pos  + 2;
        if (end_pos == std::string::npos) {
            start_pos = this->accepted_request_parsed.length();
        }
    };
};

struct http_mapp
{
    // std::unorder_map ;
    std::string action ; 
    std::string resource;
    std::string protocal;
    std::string url;
    std::string content;
    std::string content_length;

    /* data */
};

http_mapp read_http(std::string http_case) {
    http_mapp hp;
    auto line_pox  = http_case.find("\r\n");
    spdlog::info("显示line_锚点 {}", line_pox);
    std::cout << line_pox << std::endl;
    auto line = http_case.substr(0, 4);
    
    for (auto line : http_case){
        spdlog::info("traverse line {}", line);
    }
    // spdlog::info("traverse line {}", )
    return hp;
};
// def 

int main() {
    std::string http_case = "POST /login HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 27\r\n"
        "\r\n"
        "username=admin&password=123";
    read_http(http_case);
    http_request_parser parser;
    parser.http_split(http_case);
    spdlog::info("http_case 解析已完成");
};