#include "../includes/galloc.h"


void	clear_memory(t_block *block) {
	uintptr_t	*mem = block->mem;
	for (uint64_t i = 0; i < block->mem_size; i++) {
		mem[i] = 0;
	}
	//printf("Clear memory --------------------\n");
}

void *galloc(size_t size) {

	printf("gallllooc\n");
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
	assert(block->mem_size < 100000);
	debug_mode(block, "MALLOC", size);
	pthread_mutex_unlock(&(g_main_mutex));
	if (block->prev) {
		printf("Check slopaing %lx - %lx\n", (uint64_t)block->prev->mem + block->prev->mem_size, (uint64_t)block);
		if((uint64_t)block->prev->mem + block->prev->mem_size > (uint64_t)block) {
			uintptr_t *mem = (uintptr_t  *)block;
			printf("sloooopiiiiibng -------- detected   ----------------\n");
			printf("%02lx , %02lx , %02lx, %02lx\n", (uint64_t)mem[1], (uint64_t)mem[2], (uint64_t)mem[3], (uint64_t)mem[1]);
			//show_dump(block->prev);
			printf("End sloping\n\n");
		}
	}
	assert(block->mem_size < 200);
	return ptr;
}
