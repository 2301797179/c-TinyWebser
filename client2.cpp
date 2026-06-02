#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    int clientsocketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);
    connect(clientsocketfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    char buffer[1024] = {0};
    std::strcpy(buffer, "Hello server");
    int client_sended = send(clientsocketfd, buffer, sizeof(buffer) - 1, 0);
    

}
