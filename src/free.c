#include "../includes/galloc.h"

// remove a completly header and remove the memory with munmap
// munmap in error returns -1
void	remove_header(t_header *header)
{
	current_allocs_size(FREE, header->current_size);
	if (header == get_main_header())
	{
		set_main_header(header->next);
		pthread_mutex_unlock(get_global_mutes());
		if (munmap(header, header->size) == -1)
			write(2, "munmap(): fatal error\n", 22);
		return;
	}
	if (header->prev)
		header->prev->next = header->next;
	if (header->next)
		header->next->prev = header->prev;
	pthread_mutex_unlock(get_global_mutes());
	if (munmap(header, header->size) == -1)
		write(2, "munmap(): fatal error\n", 22);
}

void	free(void *ptr)
{
	if (!ptr || !ptr_was_in_headers((uintptr_t)ptr)) // check if the ptr is from our malloc
		return ;

	pthread_mutex_lock(get_global_mutes());
	t_block	*block = (t_block *)((char *)ptr - sizeof(t_block));
	t_header *header = find_header_from_block(block);
	if (!header)
	{
		ft_printf("%p\n", ptr);
		show_alloc_mem();
		write(2, "free(): invalid pointer\n", 24);
		pthread_mutex_unlock(get_global_mutes());
		return ;
	}
	block->state = FREE;
	debug_mode(block, "FREE", 0);
	defragment_header(&block);
	// remove header if is not the first or is large
	if (block == header->blocks && block->next == NULL && block->state == FREE \
		&& !(!header->next && get_main_header() == header && header->type != LARGE))
	{
		//pthread_mutex_unlock(get_global_mutes()); // called inside of remove_header()
		remove_header(header); // remove this header and free the memory
		return ;
	}
	if (!block->next && block->prev)
	{ // remove block from the block list
		header->current_size -= block->size;
		current_allocs_size(FREE, block->size);
		block->prev->next = NULL;
	}
	block->mem_size = block->size - sizeof(t_block);
	pthread_mutex_unlock(get_global_mutes());
}
