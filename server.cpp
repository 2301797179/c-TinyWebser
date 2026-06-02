#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>
void handle_request(int serversocketfd )
{
    char buffer[1024] = {0};
    int byte_received = recv(serversocketfd, buffer, sizeof(buffer) - 1, 0);
    if (byte_received > 0) {
    std::cout << "显示收到的数据 " << buffer << std::endl;
    }
    // else {
    // std::cout << "未收到数据" << std::endl;
    // };
    close(serversocketfd);  

}
int main() {
    int listensocketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);
    bind(listensocketfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(listensocketfd, 5);
    
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    while (true) {
        int serversocketfd = accept(listensocketfd, (struct sockaddr*)&client_addr, &client_addr_len);
        std::thread server_thread(handle_request, serversocketfd);
        server_thread.detach();
            
            
    }
    // char buffer[1024] = {0};
    // int byte_received = recv(serversocketfd, buffer, sizeof(buffer) - 1, 0);
    // if (byte_received > 0) {
    // std::cout << "显示收到的数据 " << buffer << std::endl;
    // }
    // else {
    // std::cout << "未收到数据" << std::endl;
    // };  

// 同时接受多个请求
// 开启多线程， 多线程中包含

}



