#include "../../includes/galloc.h"


t_type get_type_header(size_t size)
{
	if (size <= N)
		return TINY;
	else if (size <= M)
		return SMALL;
	else
		return LARGE;
}

int get_size_header(size_t size)
{
	size_t padding = (size % 16) ? 16 - (size % 16) : 0;
	if (size <= N)
		return (N + sizeof(t_block)) * 100 + sizeof(t_header) + padding;// sysconf(_SC_PAGESIZE)) ;
	else if (size <= M)
		return (M + sizeof(t_block)) * 100 + sizeof(t_header) + padding;
	else    //this is the calc for the padding
		return size + sizeof(t_block) + sizeof(t_header) + padding;
}
