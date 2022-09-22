// https://stackoverflow.com/a/11461302

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "../utils/utils.h"

void child(int socket, int size)
{
    struct timespec before, after;

    char buffer[size];
    char *message = genarray(size);

    clock_gettime(CLOCK_MONOTONIC, &before);

    write(socket, message, size);
    int n = read(socket, buffer, size);

    clock_gettime(CLOCK_MONOTONIC, &after);

    free(message);

    int64_t diff = difftimespec_ns(after, before);

    printf("%ld,%ld,%ld\n", before.tv_nsec, after.tv_nsec, diff);
}

void parent(int socket, int size)
{
    char *buffer = malloc(size);
    int n = read(socket, buffer, size);
    write(socket, buffer, sizeof(buffer));
    free(buffer);
}

int main(int argc, char const *argv[])
{
    int fd[2];
    static const int pSocket = 0;
    static const int cSocket = 1;
    pid_t pid;

    socketpair(PF_LOCAL, SOCK_STREAM, 0, fd);

    // https://stackoverflow.com/a/31997755
    // int yes = 1;
    // setsockopt(fd[pSocket], IPPROTO_TCP, TCP_NODELAY, (char *)&yes,
    // sizeof(int));

    pid = fork();
    if (pid == 0)
    {
        close(fd[pSocket]);
        child(fd[cSocket], strtol(argv[1], NULL, 10));
    }
    else
    {
        close(fd[cSocket]);
        parent(fd[pSocket], strtol(argv[1], NULL, 10));
    }
    exit(0);
    return 0;
}
