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
	ft_printf("malloc size %u\n", size);
	if (size == 0) {
		/*ft_printf("0 is validdd???? -0---------------------");
			return NULL;*/
		size = 1;
	}
	ft_printf("mutex lock?\n");
	pthread_mutex_lock(&(g_main_mutex));
	ft_printf("lock mutex malloc\n");
	ft_printf("malloc after\n");
	t_header	*header = get_header_node(size);
	if (!header)
	{
		ft_printf("Nooooooooooooooooooooooooo-----\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	ft_printf("aqui -1\n");
	t_block *block = get_block_from_header(size, header);
	ft_printf("aqui 0\n");
	if (!block)
	{
		ft_printf("2Nooooooooooooooooooooooooo-----\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	ft_printf("aqui 1\n");
	debug_mode(block, "MALLOC", size);
	ft_printf("aqui 1.4\n");
	//printf("current block size: %lu size needed: %lu\n", block->size - sizeof(t_block), size);
	if (block->size - sizeof(t_block) > size + 15)
		split_block(block, size);
	ft_printf("aqui 1.9\n");
	void *ptr = asign_block(size, block);
	ft_printf("aqui 1.99\n");
	//if (CALLOC)
		//clear_memory(block);
	debug_mode(block, "MALLOC", size);
	ft_printf("aqui 2\n");
	if (block->prev){ // check
		if ((uint64_t)block->prev->mem + block->prev->mem_size > (uint64_t)block) {
			show_alloc_mem_ex();
			ft_printf("Este falllla %p   %u\n", block, size);
		}
		assert((uint64_t)block->prev->mem + block->prev->mem_size <= (uint64_t)block);
	}
	pthread_mutex_unlock(&(g_main_mutex));
	ft_printf("mutex unlock malloc\n");
	return ptr;
}
