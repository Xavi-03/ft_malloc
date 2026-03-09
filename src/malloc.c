#include "../includes/galloc.h"


void	clear_memory(t_block *block)
{
	uint8_t	*mem = block->mem;
	for (uint64_t i = 0; i < block->mem_size; i++) {
		mem[i] = 0;
	}
	//printf("Clear memory --------------------\n");
}

void *malloc(size_t size)
{
	if (size == 0) {
		/*ft_printf("0 is validdd???? -0---------------------");
			return NULL;*/
		size = 1;
	}
	pthread_mutex_lock(&(g_main_mutex));
	t_header	*header = get_header_node(size);
	if (!header)
	{
		ft_printf("Nooooooooooooooooooooooooo-----\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	t_block *block = get_block_from_header(size, header);
	if (!block)
	{
		ft_printf("2Nooooooooooooooooooooooooo-----\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	debug_mode(block, "MALLOC", size);
	//printf("current block size: %lu size needed: %lu\n", block->size - sizeof(t_block), size);
	if (block->size - sizeof(t_block) > size + 15)
		split_block(block, size);
	void *ptr = asign_block(size, block);

	//if (CALLOC)
		//clear_memory(block);
	debug_mode(block, "MALLOC", size);
	pthread_mutex_unlock(&(g_main_mutex));
	if (block->prev) // check
		assert((uint64_t)block->prev->mem + block->prev->mem_size <= (uint64_t)block);
	return ptr;
}
