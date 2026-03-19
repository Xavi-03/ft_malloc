#include "../includes/galloc.h"

// if is the last block and the header allow, extend the block to new size
static void	adjust_alloc(t_header *header, t_block *block, size_t size) {
	uint8_t padding = (size % 16) ? 16 - (size % 16): 0;

	header->current_size -= block->size;
	current_allocs_size(FREE, block->size);

	block->size = size + sizeof(t_block) + padding;
	block->mem_size = block->size - sizeof(t_block);

	header->current_size += block->size;
	current_allocs_size(ASIGNED, block->size);
}

/*
	move the ptr(argument) to the block ptr and asign to (t_block *)block:
		HEADER PTR|(struct t_header)|BLOCK PTR|(struct t_block)|MEM PTR|(void *ptr)
	BEFORE												|(void *ptr)
	AFTER						  |(t_blcok *block)
*/
void	*realloc(void *ptr, size_t size)
{
	t_block		*block = ptr;
	t_header	*header = NULL;
	void		*new_ptr = NULL;
	if (!ptr) {
		return malloc(size);
	}
	if (!ptr_was_in_headers((uintptr_t)ptr)) // check if the ptr is from our malloc
    {
        void *new_ptr = malloc(size);
        return new_ptr;
    }
	if (size == 0)
    {
        free(ptr);
        return NULL;
    }
	pthread_mutex_lock(get_global_mutes());
	// move back the ptr to the block(explained above)
	block = (t_block *)((uintptr_t)block - sizeof(t_block));
	if (!block)
	{
		pthread_mutex_unlock(get_global_mutes());
		return NULL;
	}

	header = find_header_from_block(block);
	if (!header)
	{
		pthread_mutex_unlock(get_global_mutes());
		return NULL;
	}

	// check if the new size is larger or smaller than then previous size
	if (!block->next && get_type_header(block->size) == get_type_header(size) && get_type_header(size) != LARGE) {
		adjust_alloc(header, block, size);
		pthread_mutex_unlock(get_global_mutes());
		debug_mode(block, "REALLOC", 0);
		return ptr;
	}
	pthread_mutex_unlock(get_global_mutes());
	new_ptr = malloc(size);
	new_ptr = ft_memcpy(new_ptr, ptr, (block->size < size)? block->size: size);
	free(ptr);
	debug_mode((t_block *)((uintptr_t)new_ptr - sizeof(t_block)), "REALLOC", size);
	return new_ptr;
}
