#include "../includes/galloc.h"

size_t	current_allocs(int state, size_t size)
{
	static size_t current_size = 0;
	if (state == GET_MEMORY_SIZE)
		return current_size;
	else if (state == ASIGNED)
		current_size += size;
	else if (state == FREE)
		current_size -= size;
	return 0;
}

int check_current_allocs(size_t size)
{
	struct rlimit rlim;
	int r = getrlimit(RLIMIT_DATA, &rlim);
	if (r == -1)
		return 0;
	size_t current_size = current_allocs(GET_MEMORY_SIZE, 0);
	//printf("current_size\t%lu\nmax_size\t\t%lu", current_size, rlim.rlim_max);
	return 0;
}
