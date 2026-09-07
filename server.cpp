#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
#include <sys/epoll.h>
#include <fcntl.h>
#include <functional>
#include "threadpool/thread_pool.cpp"
#include "http.h"

// #include "http.cpp"
#define MAX_EVENTS 1024
#define EPOLL_TIME_OUT -1
#define RECV_FLAG 0
// #include "threadpool"

// void handle_request(int serversocketfd)
// {
//     char buffer[1024] = {0};
//     int byte_received = recv(serversocketfd, buffer, sizeof(buffer) - 1, 0);
//     if (byte_received > 0)
//     {
//         std::cout << "显示收到的数据 " << buffer << std::endl;
//     }
//     // test
//     std::string response = "HTTP/1.1 200 OK\r\n"
//                            "Content-Type: text/html; charset=utf-8\r\n"
//                            "Content-Length: 120\r\n"
//                            "\r\n"
//                            "<html><body><h2>AI 视觉推理网关（第一代原型机）</h2></body></html>";
//     // else {
//     // std::cout << "未收到数据" << std::endl;
//     // };
//     send(serversocketfd, response.data(), response.size(), 0);

//     close(serversocketfd);
// };

// int main()
// {
//     int listensocketfd = socket(AF_INET, SOCK_STREAM, 0);
//     struct sockaddr_in server_addr;
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     server_addr.sin_port = htons(8888);
//     bind(listensocketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
//     listen(listensocketfd, 5);

//     struct sockaddr_in client_addr;
//     socklen_t client_addr_len = sizeof(client_addr);
//     while (true)
//     {
//         int serversocketfd = accept(listensocketfd, (struct sockaddr *)&client_addr, &client_addr_len);
//         std::thread server_thread(handle_request, serversocketfd);
//         server_thread.detach();
//     }
// };

// void set_connection()
// {
//     int listensocketfd = socket(AF_INET, SOCK_STREAM, 0);
//     struct sockaddr_in server_addr;
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     server_addr.sin_port = htons(8888);
// }

void handle_http_request(int client_fd){
    // std::cout << "连接成功" << std::endl;
    char buf[1024] = {0};
    int recv_t = recv(client_fd, buf, sizeof(buf) - 1, RECV_FLAG);
    if (recv_t > 0) {
        std::cout<< buf << std::endl;
        http_request request;
        http_request_parser parser;
        parser.http_request_parser_runner(buf, client_fd);

        close(client_fd);
    
    }


}

void network()
{
    int listensocketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);
    bind(listensocketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listensocketfd, 5);

    int epoll_fd = epoll_create(1);
    struct epoll_event event;
    int flag = fcntl(listensocketfd, F_GETFL, O_NONBLOCK);
    flag = flag | O_NONBLOCK;
    fcntl(listensocketfd, F_SETFL, flag);
    event.data.fd = listensocketfd;
    event.events = EPOLLIN | EPOLLRDHUP;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listensocketfd, &event);
    struct epoll_event ready_events[MAX_EVENTS];

    // 初始化线程池
    threadpool thread_pool(10);
    while (true)
    {
        // struct epoll_event ready_event[MAX_EVENTS];
        int epoll_event_flags = epoll_wait(epoll_fd, ready_events, MAX_EVENTS, EPOLL_TIME_OUT);
        if (epoll_event_flags > 0)
        {
            for (int ready_event_index = 0; ready_event_index < epoll_event_flags; ++ready_event_index)
            {
                // struct http_request request;
                // struct sockaddr_in client_addr;
                struct epoll_event &ready_event = ready_events[ready_event_index];
                if (ready_event.data.fd == listensocketfd)
                {
                    int client_fd = accept(listensocketfd, nullptr, nullptr);
                    if (client_fd > 0)
                    {

                        int client_flag = fcntl(client_fd, F_GETFL, O_NONBLOCK);
                        client_flag = client_flag | O_NONBLOCK;
                        fcntl(client_fd, F_SETFL, client_flag);
                        event.data.fd = client_fd;
                        event.events = EPOLLIN | EPOLLRDHUP;
                        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
                        
                    };
                }
                else {
                    int current_ready_eventfd = ready_event.data.fd;
                    thread_pool.push([current_ready_eventfd]{
                        return handle_http_request(current_ready_eventfd);
                    });
                }

                // recv(listensocketfd, );
            }
        }
    }
};

int main(){
    network();
};
