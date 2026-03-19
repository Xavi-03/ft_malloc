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
	size_t total;
    size_t pagesize = sysconf(_SC_PAGESIZE);  // 4096

    if (size <= N)
        total = (N + sizeof(t_block)) * 100 + sizeof(t_header);
    else if (size <= M)
        total = (M + sizeof(t_block)) * 100 + sizeof(t_header);
    else
        total = size + sizeof(t_block) + sizeof(t_header);

    return (total + pagesize - 1) / pagesize * pagesize;
}

// checking if the ptr is in the range of the headers
int ptr_was_in_headers(uintptr_t ptr) {
	t_header *header = get_main_header();
	while (header)
	{
		if ((uintptr_t)header < ptr && ptr < (uintptr_t)header + header->size)
			return 1;
		header = header->next;
	}
	return 0;
}
