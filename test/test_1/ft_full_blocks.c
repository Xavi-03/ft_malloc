#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include "../includes/galloc.h"

extern void show_alloc_mem(void);

int main(void) {
	void *ptr1;
	void *ptr2;
	for (int i = 0; i < 101; i++) {
		if (i % 2)
			ptr1 = malloc(2048);
		else
			ptr2 = malloc(2048);
	}
	//malloc(1);
	show_alloc_mem();
//	free(ptr2);
//	show_alloc_mem();
//	malloc(1);
//	show_alloc_mem();
//	malloc(64);
//	show_alloc_mem();
//	free(ptr1);
//	show_alloc_mem();
//	malloc(128);
//	show_alloc_mem();
}
