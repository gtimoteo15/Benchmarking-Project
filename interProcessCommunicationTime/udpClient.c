// https://www.geeksforgeeks.org/udp-server-client-implementation-c/

// Client side implementation of UDP client-server model
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
    struct timespec before, after;
    struct sockaddr_in servaddr;
    int sockfd;
    int n;
    int len;

    int size = strtol(argv[1], NULL, 10);

    char *buffer = malloc(size);
    char *message = genarray(size);


    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    clock_gettime(CLOCK_MONOTONIC, &before);

    if (size > 65536)
    {
        int remainder = size / 65536;
        for (int i = 0; i < remainder; i++)
        {
            char *buffer = malloc(65536);
            char *message = genarray(65536);

            sendto(sockfd, (const char *)message, 65536, MSG_CONFIRM, (const struct sockaddr *)&servaddr,
                   sizeof(servaddr));

            n = recvfrom(sockfd, (char *)buffer, 65536, MSG_DONTWAIT, (struct sockaddr *)&servaddr, &len);
        }
    }
    else
    {
        sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));

        n = recvfrom(sockfd, (char *)buffer, size, MSG_DONTWAIT, (struct sockaddr *)&servaddr, &len);
    }
    free(buffer);
    free(message);

    clock_gettime(CLOCK_MONOTONIC, &after);
    int64_t diff = difftimespec_ns(after, before);
    printf("%ld,%ld,%ld\n", before.tv_nsec, after.tv_nsec, diff);

    close(sockfd);
    return 0;
}
