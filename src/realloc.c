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
	ft_printf("lock mutex realloc\n");
	// move back the ptr to the block(explained above)
	block = (t_block *)((char *)block - sizeof(t_block));
	if (!block)
	{
		ft_printf("unlcok mutex\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	header = find_header_from_block(block);
	if (!header)
	{
		ft_printf("unlcok mutex\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return NULL;
	}
	// check if the new size is larger or smaller than then previous size
	if (!block->next) {
		adjust_alloc(header, block, size);
		ft_printf("unlcok mutex\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return ptr;
	}
	ft_printf("unlcok mutex\n");
	pthread_mutex_unlock(&(g_main_mutex));
	new_ptr = malloc(size);
	new_ptr = ft_memcpy(new_ptr, ptr, block->size - sizeof(t_block));
	free(ptr);

	debug_mode(block, "REALLOC", 0);

//	pthread_mutex_unlock(&(g_main_mutex));
	return new_ptr;
}
