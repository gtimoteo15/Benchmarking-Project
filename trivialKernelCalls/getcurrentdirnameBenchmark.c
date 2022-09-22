#include "../utils/utils.h"
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char *hostname;
    size_t hostnameLength = 32;

    struct timespec before, after;

    puts("iteration,before,after,diff");

    for (int iteration = 0; iteration < 1000; iteration++)
    {
        clock_gettime(CLOCK_MONOTONIC, &before);

        getcwd(0,0);

        clock_gettime(CLOCK_MONOTONIC, &after);

        int64_t diff = difftimespec_ns(after, before);

        printf("%d,%ld,%ld,%ld\n", iteration, before.tv_nsec, after.tv_nsec, diff);
    }
    return 0;
}
