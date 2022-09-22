#include "../utils/utils.h"
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    struct timespec before, after;

    puts("iteration,before,after,diff");

    for (int iteration = 0; iteration < 1000; iteration++)
    {
        clock_gettime(CLOCK_MONOTONIC, &before);

        int test = getcpu(0, 0);

        clock_gettime(CLOCK_MONOTONIC, &after);

        int64_t diff = difftimespec_ns(after, before);

        printf("%d,%ld,%ld,%ld, %d\n", iteration, before.tv_nsec, after.tv_nsec, diff, test);
    }
    return 0;
}
