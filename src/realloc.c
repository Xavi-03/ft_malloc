#include "../includes/galloc.h"

static void	adjust_alloc(t_header *header, t_block *block, size_t size) {
	uint8_t padding = 16 - (size % 16);
	padding = (padding == 16) ? 0 : padding;

	header->current_size -= block->size;
	current_allocs_size(FREE, block->size);


	block->size = size + sizeof(t_block) + padding;
	block->mem_size = block->size - sizeof(t_block);

	header->current_size += block->size;
	current_allocs_size(ASIGNED, block->size);
}

/*
	move the ptr(argument) to the block ptr and asign to (t_block *)block:
		HEADER PTR|...(struct)|...|BLOCK PTR|...(struct)|MEM PTR|...
	BEFORE												|(void *ptr)
	AFTER						  |(t_blcok *block)
*/
void	*realloc(void *ptr, size_t size)
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
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	header = find_header_from_block(block);
	if (!header)
	{
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	// check if the new size is larger or smaller than then previous size
	if (!block->next && get_type_header(block->size) == get_type_header(size) && get_type_header(size) != LARGE) {
		adjust_alloc(header, block, size);
		pthread_mutex_unlock(&(g_main_mutex));
		debug_mode(block, "REALLOC", 0);
		return ptr;
	}
	pthread_mutex_unlock(&(g_main_mutex));
	new_ptr = malloc(size);
	new_ptr = ft_memcpy(new_ptr, ptr, block->size - sizeof(t_block));
	free(ptr);
	debug_mode((t_block *)((uintptr_t)new_ptr - sizeof(t_block)), "REALLOC", size);

//	pthread_mutex_unlock(&(g_main_mutex));
	return new_ptr;
}
