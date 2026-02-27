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
			printf("\tblock:\t\t%p\n\tmem:\t\t%p\n\tsize:\t\t%lu\n\treal_size:\t%lu\n\tstate:\t\t%s\n", block, block->mem, block->size, block->real_size, block_state(block->state));
			block = block->next;
			printf("\n\n");
		}
		printf("\n\n");
		header = header->next;
	}
}

void	show_alloc_mem_ex(void)
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
			printf("\tblock:\t\t%p\n\tmem:\t\t%p\n\tsize:\t\t%lu\n\treal_size:\t%lu\n\tstate:\t\t%s\n", block, block->mem, block->size, block->real_size, block_state(block->state));


			show_dump(block);
			printf("\n");
			block = block->next;
		}
		printf("\n\n");
		header = header->next;
	}
}

void	show_dump(t_block *block) {
	uint8_t		*mem = NULL;

	mem = block->mem;
	printf("\n\t");
	for (uint64_t i = 0; i < block->real_size; i++) {
		printf("%02x", mem[i]);

		if ((i + 1) % 16 == 0)
			printf("\n\t");
		else if (i + 1 != block->real_size && (i + 1) % 8 == 0)
			printf("  ");
		else if (i + 1 == block->real_size)
			printf("\n\n\n\n");
		else
			printf(" ");
	}
}

void debug_mode(t_block *block, char *type) {
	if (SHOW_MALLOC)
		printf("\t##  %s  ##\n\n", type);
	if (SHOW_MALLOC_INFO)
		printf("\tblock:\t\t%p\n\tmem:\t\t%p\n\tsize:\t\t%lu\n\treal_size:\t%lu\n", block, block->mem, block->size, block->real_size);
	if (SHOW_DUMP) {
		show_dump(block);
		printf("\n");
	}
}
