// https://www.geeksforgeeks.org/udp-server-client-implementation-c/

// Server side implementation of UDP client-server model
#include "../utils/utils.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 8080

// Driver code
int main(int argc, char const *argv[])
{
    struct timespec after;
    int sockfd;
    int len;
    int n;

    int size = strtol(argv[1], NULL, 10);

    char *buffer = malloc(size);
    char *message = genarray(size);
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr); // len is value/result

    if(size > 65536)
    {
        int remainder = size / 65536;
        for (int i = 0; i < remainder; i++)
        {
            n = recvfrom(sockfd, (char *)buffer, 65536, MSG_DONTWAIT, (struct sockaddr *)&cliaddr, &len);

            sendto(sockfd, (const char *)message, 65536, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        }
    }
    else
    {
        n = recvfrom(sockfd, (char *)buffer, size, MSG_DONTWAIT, (struct sockaddr *)&cliaddr, &len);
        sendto(sockfd, (const char *)message, 65536, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    }

    clock_gettime(CLOCK_MONOTONIC, &after);
    printf("%ld\n", after.tv_nsec);

    free(buffer);
    free(message);

    return 0;
}
