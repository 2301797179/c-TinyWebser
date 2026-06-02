#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (sockaddr * )&addr, sizeof(addr));
    listen(server_fd, 5);
    std::cout << "Server started...\n";

    while(true) {
        int client_fd = accept(server_fd, nullptr, nullptr);

        char buffer[1024] = {0};
        int n = recv(client_fd, buffer, sizeof(buffer), 0);

        send(client_fd, buffer, n, 0);

        close(client_fd);
    }

}




