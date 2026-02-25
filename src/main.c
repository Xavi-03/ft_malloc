#include "../includes/galloc.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>



#include <stdio.h>
#include <sys/resource.h>

void print_memory_limits(void)
{
    struct rlimit lim;

    galloc(200);
    galloc(20);
    galloc(200);
    galloc(20000);
    galloc(20);
    galloc(20000);
    show_mallocs();
    void *ptr;
    printf("1 %p\n", ptr);
    ptr = malloc(10000);
    printf("2 %p\n", ptr);
    free(ptr);
    printf("3 %p\n", ptr);
    ptr = malloc(10000);
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
	char *ptr;
    //print_memory_limits();
    for (int i = 0; i < 100; i++)
    	ptr = galloc(1000000);
    ptr[0] = 'a';
    //gfree(ptr);
    return 0;
}
