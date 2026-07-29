#include <iostream>
#include <string>

struct http_mapp
{
    std::string action ; 
    std::string resource;
    std::string protocal;
    std::string url;
    std::string content;
    std::string content_length;

    /* data */
};

http_mapp read_http(std::string http_case) {
    
    http_mapp hp ;
    return hp;
};




int main() {
    std::string http_case = "POST /login HTTP/1.1\r\n"
        "Host: example.com\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: 27\r\n"
        "\r\n"
        "username=admin&password=123";
    
    

    
    

};