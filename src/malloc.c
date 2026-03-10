#include "../includes/galloc.h"


void	clear_memory(t_block *block)
{
	uint8_t	*mem = block->mem;
	for (uint64_t i = 0; i < block->mem_size; i++) {
		mem[i] = 0;
	}
}

void *malloc(size_t size)
{
	if (size == 0) {
		size = 1;
	}
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
	debug_mode(block, "MALLOC", size);
	if (block->size - sizeof(t_block) > size + 15)
		split_block(block, size);
	void *ptr = asign_block(size, block);
	//if (CALLOC)
		//clear_memory(block);
	debug_mode(block, "MALLOC", size);
	if (block->prev){ // check
		assert((uint64_t)block->prev->mem + block->prev->mem_size <= (uint64_t)block);
	}
	pthread_mutex_unlock(&(g_main_mutex));
	return ptr;
}
