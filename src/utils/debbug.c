#include "../../includes/galloc.h"


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

static char *header_type(t_type type) {
	if (type == TINY)
		return "TINY";
	else if (type == SMALL)
		return "SMALL";
	else if (type == LARGE)
		return "LARGE";
	else
		return "ERROR";
}

void	show_alloc_mem(void)
{
	pthread_mutex_lock(get_global_mutes());
	t_header	*header = get_main_header();
	t_block		*block = NULL;

	ft_printf("Current memory use: %u\n", current_allocs_size(GET_MEMORY_SIZE, 0));
	while (header)
	{
		ft_printf("\nheader: %p\n\tsize: %u\n\tcurrent: %u\n\ttype: %s\n\n", header, header->size, header->current_size, header_type(header->type));
		block = header->blocks;
		while (block)
		{
			ft_printf("\tblock:\t\t%p\n\tmem:\t\t%p\n\tsize:\t\t%u\n\tmem_size:\t%u\n\tstate:\t\t%s\n", block, block->mem, block->size, block->mem_size, block_state(block->state));
			block = block->next;
			ft_printf("\n\n");
		}
		ft_printf("\n");
		header = header->next;
	}
	pthread_mutex_unlock(get_global_mutes());
}

void	show_alloc_mem_ex(void)
{
	pthread_mutex_lock(get_global_mutes());
	t_header	*header = get_main_header();
	t_block		*block = NULL;

	ft_printf("Current memory use: %u\n", current_allocs_size(GET_MEMORY_SIZE, 0));
	while (header)
	{
		ft_printf("\nheader: %p\n\tsize: %u\n\tcurrent: %u\n\ttype: %s\n\n", \
			header, header->size, header->current_size, header_type(header->type));
		block = header->blocks;
		while (block)
		{
			ft_printf("\tblock:\t\t%p\n\tmem:\t\t%p\n\tsize:\t\t%u\n\tmem_size:" \
				"\t%u\n\tstate:\t\t%s\n", block, block->mem, block->size, \
				block->mem_size, block_state(block->state));
			show_dump_full_mem(block);
			block = block->next;
		}
		ft_printf("\n");
		header = header->next;
	}
	pthread_mutex_unlock(get_global_mutes());
}

static void	print_mem(uint8_t data) {
	if (data < 16)
		ft_printf("0%x", data);
	else
		ft_printf("%x", data);
}

void	show_dump(t_block *block) {
	uint8_t		*mem = NULL;

	mem = block->mem;
	ft_printf("\n\t");
	for (uint64_t i = 0; i < block->mem_size; i++) {
		print_mem(mem[i]);

		if (i + 1 != block->mem_size && (i + 1) % 64 == 0)
			ft_printf("\n\n\t");
		else if (i + 1 != block->mem_size && (i + 1) % 16 == 0)
			ft_printf("\n\t");
		else if (i + 1 != block->mem_size && (i + 1) % 8 == 0)
			ft_printf("  ");
		else if (i + 1 == block->mem_size)
			ft_printf("\n\n\n");
		else
			ft_printf(" ");
	}
}

void	show_dump_full_mem(t_block *block) {
	uint8_t		*mem = NULL;

	mem = (void *)block;
	ft_printf("\n\t");
	for (uint64_t i = 0; i < block->size; i++) {
		print_mem(mem[i]);

		if (i + 1 != block->size && (i + 1) % 64 == 0)
			ft_printf("\n\n\t");
		else if (i + 1 != block->size && (i + 1) % 16 == 0)
			ft_printf("\n\t");
		else if (i + 1 != block->size && (i + 1) % 8 == 0)
			ft_printf("  ");
		else if (i + 1 == block->size)
			ft_printf("\n\n\n");
		else
			ft_printf(" ");
	}
}

void debug_mode(t_block *block, char *type, size_t size) {
	if (!block)
		return;
	if (CALLOC)
		clear_memory(block);
	if (SHOW_MALLOC && type)
		ft_printf("\n\t##  %s  ##  block size %u  ##  mem size %u  ##  param size %u  ##\n", type, block->size, block->mem_size, size);
	if (SHOW_MALLOC_INFO)
		ft_printf("\n\tblock:\t\t%p\n\tmem:\t\t%p\n\tsize:\t\t%u\n\tmem_size:\t%u\n\n", block, block->mem, block->size, block->mem_size);
	if (SHOW_DUMP)
		show_dump(block);
}
