#include "../includes/galloc.h"


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

static char	*block_state(t_state state) {
	if (state == ASIGNED)
		return "ASIGNED";
	else if (state == FREE)
		return "FREE";
	else
		return "ERROR";
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
			printf("\tblock:\t\t%p\n\tmem:\t\t%p\n\tsize:\t\t%lu\n\tpadding:\t%lu\n\tstate:\t\t%s\n", block, block->mem, block->size, block->padding, block_state(block->state));
			block = block->next;
			printf("\n\n");
		}
		printf("\n\n");
		header = header->next;
	}
}
