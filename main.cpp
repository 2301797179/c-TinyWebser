#include <iostream>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

int main() {
    printf("main function start!\n");
    int listensocketfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);
    bind(listensocketfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(listensocketfd, 5);


}



