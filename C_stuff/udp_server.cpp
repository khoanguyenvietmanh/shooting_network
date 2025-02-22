// Server side implementation of UDP client-server model
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr{}, cliaddr{};

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *) &servaddr,
             sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); //len is value/resuslt

    while (true) {
        n = recvfrom(sockfd, (char *) buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *) &cliaddr,
                     reinterpret_cast<socklen_t *>(&len));
        buffer[n] = '\0';
        printf("Received : %s\n", buffer);
    }


//    char hello[] = "Hello from server";
//
//    sendto(sockfd, (const char *) hello, strlen(hello),
//           MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
//           len);
//    printf("Hello message sent.\n");

    return 0;
}
