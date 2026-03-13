#include <stdlib.h>
#include "../includes/galloc.h"

int main(void) {
	for (int i = 0; i < 1; i++) {
		if (!malloc(1025))
			ft_printf("aaaa\n");
	}
	show_alloc_mem();
}
