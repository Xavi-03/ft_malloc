#include "../includes/galloc.h"
#include <stdlib.h>
#include <time.h>

void	*threads(void *ptr)
{
	printf("mutex: %p\n", &g_main_mutex);
	void *ptr1 = galloc(15);
//	show_mallocs();
	galloc(1);
	galloc(1);
	galloc(1);
	galloc(1);
	galloc(1);
	//gfree(ptr1);
	printf("b\n");
	return NULL;
}

int main(void) {
	pthread_t id;
	galloc(1);
	pthread_create(&id, NULL, threads, NULL);
	printf("a\n");
	printf("mutex: %p\n", &g_main_mutex);
	void *ptr1 = galloc(30);
	sleep(10);
	galloc(77);
	galloc(1);
	galloc(1);
	galloc(1);
	show_mallocs();
	sleep(5);
	pthread_join(id, NULL);
	/*void *ptr2 = galloc(120);
	void *ptr3 = galloc(42);

	void *ptr4 = galloc(400);
	void *ptr5 = galloc(200);
	void *ptr6 = galloc(600);

	void *ptr7 = galloc(354535);
	void *ptr8 = galloc(43453452);
	void *ptr9 = galloc(4234242);*/

	/*show_mallocs();

	gfree(ptr3);
	gfree(ptr2);
	gfree(ptr1);

	show_mallocs();

	gfree(ptr6);
	gfree(ptr5);
	gfree(ptr4);

	show_mallocs();

	gfree(ptr7);
	gfree(ptr8);
	gfree(ptr9);*/

	return 0;
}
