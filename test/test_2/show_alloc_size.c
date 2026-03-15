#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "../includes/galloc.h"

extern void show_alloc_mem(void);

int main(void) {
	int n = 128;
	int m = 1024;

	void *ptr1 = malloc(1);
	void *ptr2 = malloc(n);

	void *ptr3 = malloc(n + 1);
	void *ptr4 = malloc(m);

	void *ptr5 = malloc(m + 1);
	void *ptr6 = malloc(m * m);

	free(ptr1);
	free(ptr2);

	free(ptr3);
	free(ptr4);

	free(ptr5);
	free(ptr6);
}
