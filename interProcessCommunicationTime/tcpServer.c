// https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 52460
#define SA struct sockaddr

void chat(int connfd, int size)
{
    struct timespec after;
    char *buffer = malloc(size);

    if(size > 65536)
    {
        int sizeStor = size;
        int remainder = size % 65536;
        for (int i = 0; i < remainder; i++)
        {
            read(connfd, buffer, 65536);
        }
    }
    else
    {
        read(connfd, buffer, size);
    }

    clock_gettime(CLOCK_MONOTONIC, &after);
    printf("%ld\n", after.tv_nsec);

    if (size > 65536)
    {
        int sizeStor = size;
        int remainder = size % 65536;
        for (int i = 0; i < remainder; i++)
        {
            write(connfd, buffer, 65536);
        }
    }
    else
    {
        write(connfd, buffer, 65536);
    }

    free(buffer);
}

int main(int argc, char const *argv[])
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    long bufferSize = strtol(argv[1], NULL, 10);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

    listen(sockfd, 5);
    len = sizeof(cli);

    connfd = accept(sockfd, (SA *)&cli, &len);
    chat(connfd, bufferSize);
    close(sockfd);
    return 0;
}
