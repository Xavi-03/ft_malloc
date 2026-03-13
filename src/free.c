#include "../includes/galloc.h"

// remove a completly header and remove the memory with munmap
// munmap in error returns -1
void	remove_header(t_header *header)
{
	current_allocs_size(FREE, header->current_size);
	if (header == get_main_header())
	{
		set_main_header(header->next);
		if (munmap(header, header->size) == -1)
		{
			write(2, "munmap(): fatal error\n", 22);
			pthread_mutex_unlock(&(g_main_mutex));
			*(volatile char *)0 = 0; //my own abort
		}
		return;
	}
	if (header->prev)
		header->prev->next = header->next;
	if (header->next)
		header->next->prev = header->prev;
	if (munmap(header, header->size) == -1)
	{
		write(2, "munmap(): fatal error\n", 22);
		pthread_mutex_unlock(&(g_main_mutex));
		*(volatile char *)0 = 0; //my own abort
	}
}

void	free(void *ptr)
{
	if (!ptr)
		return ;

	pthread_mutex_lock(&(g_main_mutex));
	t_block	*block = (t_block *)((char *)ptr - sizeof(t_block));
	t_header *header = find_header_from_block(block);

	if (!header)
	{
		write(2, "free(): invalid pointer\n", 24);
		pthread_mutex_unlock(&(g_main_mutex));
		*(volatile char *)0 = 0; //my own abort
	}

	block->state = FREE;
	debug_mode(block, "FREE", 0);
	defragment_header(&block);

	if (get_last_block(header->blocks) == header->blocks \
		&& header->blocks->state == FREE)
	{
		remove_header(header); // remove this header and free the memory
		pthread_mutex_unlock(&(g_main_mutex));
		return ;
	}
	else if (!block->next && block->prev)
	{
		header->current_size -= block->size;
		current_allocs_size(FREE, block->size);
		block->prev->next = NULL;
	}

	block->mem_size = block->size - sizeof(t_block);
	pthread_mutex_unlock(&(g_main_mutex));
}
