#include "../includes/galloc.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>


#include <stdio.h>
#include <sys/resource.h>

void print_memory_limits(void)
{
    struct rlimit lim;

    galloc(200);
    galloc(200);
    galloc(200);
    galloc(200);
    galloc(200);
    galloc(200);
    galloc(200);
    galloc(20);
    galloc(20);
    galloc(20);
    galloc(20);
    galloc(20);
    galloc(20);
    galloc(20);
    show_mallocs();
    void *ptr;
    //printf("1 %p\n", ptr);
    ptr = malloc(10000);
    //printf("2 %p\n", ptr);
    free(ptr);
    //printf("3 %p\n", ptr);
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

void *memory() {

	for (int i = 0; i < 4; i++) {
		galloc(1);
	}
	return NULL;
}

void process_mem(void) {

	//pthread_t ida;
	/*for (int i = 0; i < 3; i++)
		pthread_create(&ida, NULL, memory, NULL);

	for (int i = 0; i < 4; i++) {
		galloc(1);
		}
		sleep(3);*/
	galloc(1);
	char *ptr = galloc (1);
	gfree(ptr);
	ptr = galloc(1);
	gfree(ptr);
	char *abc= galloc(100);
	//abc[127] = 42;
	//abc = galloc(33);
	abc[0] = 43;
	printf("acabado\n");
	show_mallocs();
	//show_alloc_mem_ex();
}

void ft_memory() {
	for (int i = 0; i < 3; i++) {
		galloc(1);
	}
	show_mallocs();
	void *ptr = galloc(1);
	gfree(ptr);
	gfree(ptr);
	show_mallocs();
}

int main(void)
{
	//char *ptr;
    //print_memory_limits();
    process_mem();
    //ft_memory();
    //gfree(ptr);
    return 0;
}
