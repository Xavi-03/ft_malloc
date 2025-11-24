#include "../includes/galloc.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>



#include <stdio.h>
#include <sys/resource.h>

void print_memory_limits(void)
{
    struct rlimit lim;

    if (getrlimit(RLIMIT_AS, &lim) == 0)
    {
        printf("Virtual address space limit: ");
        if (lim.rlim_cur == RLIM_INFINITY)
            printf("unlimited\n");
        else
            printf("%lu bytes (%.2f GB)\n",
                   (unsigned long)lim.rlim_cur,
                   (double)lim.rlim_cur / (1024 * 1024 * 1024));
    }

    if (getrlimit(RLIMIT_DATA, &lim) == 0)
    {
        printf("Heap (data segment) limit: ");
        if (lim.rlim_cur == RLIM_INFINITY)
            printf("unlimited\n");
        else
            printf("%lu bytes (%.2f MB)\n",
                   (unsigned long)lim.rlim_cur,
                   (double)lim.rlim_cur / (1024 * 1024));
    }
}

int main(void)
{
    print_memory_limits();
    return 0;
}
