#ifndef HTTP_REQUEST_PARSER
#define HTTP_REQUEST_PARSER

#include <string>
#include <unordered_map>
#include <string>
#include <unordered_map>
// #define SPDLOG_HEADER_ONLY
// #include "spdlog/spdlog.h"


struct http_request_line
{
    std::string request_line_method;
    std::string request_line_uri;
    std::string request_line_version;
    /* data */
};

// struct http_request_head
// {
//     std::unordered_map<std::string, std::string> headers;
//     /* data */
// };
struct http_request
{
    http_request_line request_line;
    std::unordered_map<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> body;
};
enum request_methods
{
    GET,
    POST,
    PUT,
    DELETE
};

enum destition
{
    Host,
    Location,
    Port
};

class http_request_parser
{
public:
    // enum
    // void
    // template <size_t N>
    bool accepted_request_parse(const char *accepted_request)
    {

        std::string temp_str(accepted_request);
        size_t len = temp_str.length();

        // self.accepted_request_parsed = "";
        for (int i = this->accepted_request_parsed_idx; i <= len - 1; i++)
        {
            // if (self.accepted_request_template == )
            this->accepted_request_parsed += accepted_request[i];
            if (accepted_request[i] == '\r')
            {
                i = i + 1;
                if ((i <= len - 1) && (accepted_request[i] == '\n'))
                {
                    if ((i + 1 <= len - 1) && (accepted_request[i + 1] == '\r'))
                    {
                        i = i + 1;
                        if ((i + 1 <= len - 1) && (accepted_request[i + 1] == '\n'))
                        {
                            i = i + 1;
                            this->accepted_request_parsed_idx = i;
                            this->http_parse_state = HTTP_REQUEST_BODY;
                            return true;
                        };
                    };
                    this->accepted_request_parsed_idx = i;
                    return true;
                    // return this->accepted_request_parsed;
                };
            };
        };
        return false;
    };

    // void http_request_parser_runner(const char *accepted_request)
    // {
    //     accepted_request_parse(accepted_request);
    //     http_split();
    // };
    void http_request_parser_runner(const char *accepted_request, int client_fd);
    void http_parse(std::string &request);
    void http_split();
    void http_request_action();
    void http_response_send(std::string response);
    void get_http_request_line_method();
    void get_http_request_header_method();
    void send_index_response(int client_fd);
    // void get_request();
    // void

private:
    std::string accepted_request_parsed;
    int accepted_request_parsed_idx = 0;
    http_request request;
    enum http_parse_states_type
    {
        HTTP_REQUEST_LINE,
        HTTP_REQUEST_HEADER,
        HTTP_REQUEST_BODY,
        HTTP_REQUEST_SUCCESS
    };
    http_parse_states_type http_parse_state = HTTP_REQUEST_LINE;

    // std::string accepted_request_template;
};

#endif