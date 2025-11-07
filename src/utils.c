#include "../includes/galloc.h"


int get_type_header(size_t size)
{
	//printf("type size: %lu\n", size);
	if (size < N)
		return TINY;
	else if (size < M)
		return SMALL;
	else
		return LARGE;
}

int get_size_header(size_t size)
{
	if (size < N)
		return (N * 100 + sysconf(_SC_PAGESIZE)) ;
	else if (size < M)
		return M * 100 + sysconf(_SC_PAGESIZE);
	else
		return size + sysconf(_SC_PAGESIZE) + sizeof(t_block) + sizeof(t_header);
}
