#include "../includes/galloc.h"
#include <stdlib.h>
#include <time.h>


int main(void) {
	size_t i = 0;
	while(i < 250)
	{
		malloc(42);
		i += 1;
	}
	return 0;
}
