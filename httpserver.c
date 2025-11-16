#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080 //1738 backwards
#define BUFFER_SIZE 1024


int main() {
    char buffer[BUFFER_SIZE];
    char resp[] =   "HTTP/1.0 200 OK\r\n"
                    "Server: webserver-c\r\n"
                    "Content-type: text/html\r\n\r\n"
                    "<html>cats meow sometimes, hope that helps</html>\r\n";
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("webserver socket");
        return 1;
    }
    printf("socket created\n");
    

    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);
    
    if (bind(sock, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("webserver bind");
        return 1;
    }
    printf("socket bound to address");
    
    if (listen(sock, SOMAXCONN) != 0) {
        perror("werbserver listen");
    }
    printf("server listening");

    for (;;) {
        int newsock = accept(sock, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);
        if (newsock < 0) {
            perror("webserver accept");
        }
        printf("server accept\n");

        int valread = read(newsock, buffer, BUFFER_SIZE);
        if (valread < 0) {
            perror("server read\n");
            continue;
        }
        
        char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE];
        sscanf(buffer, "%s %s %s", method, uri, version);
        printf("[%s:%u] %s %s %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), method, version, uri);

        int valwrite = write(newsock, resp, strlen(resp));
        if (valwrite < 0) {
            perror("webserver (write)");
            continue;
        }
        close(newsock);
    }
    return 0;
}
