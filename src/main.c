#include "../includes/galloc.h"

int main(void) {
	void *ptr1 = galloc(15);
	void *ptr2 = galloc(120);
	void *ptr3 = galloc(42);

	void *ptr4 = galloc(400);
	void *ptr5 = galloc(200);
	void *ptr6 = galloc(600);

	void *ptr7 = galloc(354535);
	void *ptr8 = galloc(43453452);
	void *ptr9 = galloc(4234242);

	show_mallocs();

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
	gfree(ptr9);

	show_mallocs();
	return 0;
}
