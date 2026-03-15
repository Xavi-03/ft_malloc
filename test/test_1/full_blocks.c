#include <stdlib.h>



int main(void) {
	void *ptr1;
	void *ptr2;
	for (int i = 0; i < 100; i++) {
		if (i % 2)
			ptr1 = malloc(128);
		else
			ptr2 = malloc(128);
	}
	malloc(1);
	free(ptr2);
	malloc(1);
	malloc(64);
	free(ptr1);
	malloc(128);
}
