#include "../includes/galloc.h"
/*
	move the ptr(argument) to the block ptr and asign to (t_block *)block:
		HEADER PTR|...(struct)|...|BLOCK PTR|...(struct)|MEM PTR|...
	BEFORE												|(void *ptr)
	AFTER						  |(t_blcok *block)
*/
void	*regalloc(void *ptr, size_t size)
{
	t_block		*block = ptr;
	t_header	*header = NULL;
	void		*new_ptr = NULL;

	if (!ptr)
		return NULL;
	pthread_mutex_lock(&(g_main_mutex));
	// move back the ptr to the block(explained above)
	block = (t_block *)((char *)block - sizeof(t_block));
	if (!block)
	{
		printf("realloc fail 1\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	header = find_header_from_block(block);
	if (!header)
	{
		printf("realloc fail 2\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	// check if the new size is larger or smaller than then previous size
	size_t diff_size = (size > block->size)?size - block->size : block->size - size;

	if (!block->next \
		&& get_last_block(header->blocks) == block \
		&& check_header_blocks_size(diff_size, header))
	{
		block->size += diff_size;
		pthread_mutex_unlock(&(g_main_mutex));
		return ptr;
	}
	new_ptr = galloc(size);
	new_ptr = ft_memcpy(new_ptr, ptr, block->size - sizeof(t_block));
	gfree(ptr);

	debug_mode(block, "REALLOC", 0);
	pthread_mutex_unlock(&(g_main_mutex));
	return new_ptr;
}
