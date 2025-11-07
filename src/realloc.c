#include "../includes/galloc.h"

void	*regalloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&(g_main_mutex));
	t_block		*block = ptr;
	t_header	*header = NULL;
	void	*new_ptr = NULL;

	if (!ptr)
		return NULL;
	block = (t_block *)((char *)block - sizeof(t_block));
	if (!block)
		return NULL;

	header = find_header_from_block(block);
	size_t diff_size = (size > block->size)?size - block->size : block->size - size;

	if (!block->next \
		&& get_last_block(header->blocks) == block \
		&& check_header_blocks_size(diff_size, header))
	{
		block->size += diff_size;
		return ptr;
	}
	new_ptr = galloc(size);
	new_ptr = ft_memcpy(new_ptr, ptr, block->size - sizeof(t_block));
	gfree(ptr);
	pthread_mutex_unlock(&(g_main_mutex));
	return new_ptr;
}
