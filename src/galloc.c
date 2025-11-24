#include "../includes/galloc.h"



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
	//printf("current block size: %lu size needed: %lu\n", block->size - sizeof(t_block), size);
	if (block->size - sizeof(t_block) > size)
	{
		split_block(header, block, size);
	}
	void *ptr = asign_block(size, block, header);


	pthread_mutex_unlock(&(g_main_mutex));

	return ptr;
}
