#include "../includes/galloc.h"
#include <stdint.h>

// function from var debbug CALLOC
void	clear_memory(t_block *block)
{
	uint8_t	*mem = block->mem;
	for (uint64_t i = 0; i < block->mem_size; i++) {
		mem[i] = 0;
	}
}


void *malloc(size_t size)
{
	if (size == 0) // handle the case of size 0, real malloc works
		size = 1;
	pthread_mutex_lock(&(g_main_mutex));

	t_header	*header = get_header_node(size);
	if (!header)
	{
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}

	t_block *block = get_block_from_header(size, header);
	if (!block)
	{
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}

	uint8_t padding = (size % 16)? 16 - (size % 16) : 0;
	if (block->size - sizeof(t_block) > size + padding)
		split_block(block, size);
	void *ptr = asign_block(size, block);

	debug_mode(block, "MALLOC", size);
	pthread_mutex_unlock(&(g_main_mutex));
	return ptr;
}
