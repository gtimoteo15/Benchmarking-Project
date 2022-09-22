#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

// https://stackoverflow.com/a/64896093
int64_t difftimespec_ns(const struct timespec after, const struct timespec before)
{
    return ((int64_t)after.tv_sec - (int64_t)before.tv_sec) * (int64_t)1000000000UL + ((int64_t)after.tv_nsec - (int64_t)before.tv_nsec);
}

char *genarray(int size)
{
    char *arr = malloc(size);

    for (int i = 0; i < size - 1; i++)
    {
        arr[i] = 'A';
    }

    arr[size - 1] = '\0';
    return arr;
}
