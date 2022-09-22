// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

#include "../utils/utils.h"
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PORT 52460
#define SA struct sockaddr

void _sendMessage(int sockfd, int size)
{
    char *buffer = malloc(size);
    char *message = genarray(size);

    write(sockfd, message, size);
    read(sockfd, buffer, size);

    free(buffer);
    free(message);
}
void chat(int sockfd, int size)
{
    struct timespec before, after;
    clock_gettime(CLOCK_MONOTONIC, &before);

    if (size > 65536)
    {
        int sizeStor = size;
        int remainder = size % 65536;
        for (int i = 0; i < remainder; i++)
        {
            _sendMessage(sockfd, 65536);
        }
    }
    else
    {
        _sendMessage(sockfd, size);
    }

    clock_gettime(CLOCK_MONOTONIC, &after);
    int64_t diff = difftimespec_ns(after, before);
    printf("%ld,%ld,%ld\n", before.tv_nsec, after.tv_nsec, diff);
}

int main(int argc, char const *argv[])
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    long bufferSize = strtol(argv[1], NULL, 10);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    connect(sockfd, (SA *)&servaddr, sizeof(servaddr));

    chat(sockfd, bufferSize);
    close(sockfd);
}
