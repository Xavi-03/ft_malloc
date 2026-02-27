#include "../includes/galloc.h"


void	clear_memory(t_block *block) {
	uintptr_t	*mem = block->mem;
	for (uint64_t i = 0; i < block->mem_size; i++) {
		mem[i] = 0;
	}
	//printf("Clear memory --------------------\n");
}

void *galloc(size_t size) {

	if (size == 0)
		return NULL;
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
	printf("\t## START MALLOC\n");
	debug_mode(block, "MALLOC", size);
	//printf("current block size: %lu size needed: %lu\n", block->size - sizeof(t_block), size);
	if (block->size - sizeof(t_block) > size + 15)
	{
		printf("##  Split block  ##\n");
		split_block(block, size);
	}
	void *ptr = asign_block(size, block, header);

	//if (CALLOC)
	//clear_memory(block);
	printf("\t## END MALLOC\n");
	debug_mode(block, "MALLOC", size);
	pthread_mutex_unlock(&(g_main_mutex));
	return ptr;
}
