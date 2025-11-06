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

size_t	current_allocs_size(int state, size_t size)
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

void	show_mallocs(void)
{
	t_header	*header = get_main_header();
	t_block		*block = NULL;

	printf("Current memory use: %lu\n", current_allocs_size(GET_MEMORY_SIZE, 0));
	while (header)
	{
		printf("\nheader: %p\n\tsize: %lu\n\tcurrent: %lu\n\ttype: %i\n\n", header, header->size, header->current_size, header->type);
		block = header->blocks;
		while (block)
		{
			printf("\tblock:\t%p\n\tmem:\t%p\n\tsize: %lu\n\tstate: %i\n", block, block->mem, block->size, block->state);
			block = block->next;
			printf("\n\n");
		}
		printf("\n\n");
		header = header->next;
	}
}
