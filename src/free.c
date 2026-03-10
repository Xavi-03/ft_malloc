#include "../includes/galloc.h"

void	remove_header(t_header *header)
{
	current_allocs_size(FREE, header->current_size);
	if (header == get_main_header())
	{
		set_main_header(header->next);
		munmap(header, header->size);
		return;
	}
	if (header->prev)
		header->prev->next = header->next;
	if (header->next)
		header->next->prev = header->prev;
	munmap(header, header->size);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&(g_main_mutex));
	if (!ptr)
	{
		pthread_mutex_unlock(&(g_main_mutex));
		return ;
	}
	t_block	*block = (t_block *)((char *)ptr - sizeof(t_block));
	t_header *header = find_header_from_block(block);
	if (!header)
	{
		write(1, "free(): invalid pointer\n", 24);
		pthread_mutex_unlock(&(g_main_mutex));
		*(volatile char *)0 = 0; //my own abort
		return ;
	}
	block->state = FREE;
	defragment_header(&block);
	if (get_last_block(header->blocks) == block \
		&& header->blocks->state == FREE) {
		remove_header(header);
		pthread_mutex_unlock(&(g_main_mutex));
		return ;
	}
	else if (!block->next && block->prev)
	{
		header->current_size -= block->size;
		current_allocs_size(FREE, block->size);
		block->prev->next = NULL;
	}
	debug_mode(block, "FREE", 0);
	block->mem_size = block->size - sizeof(t_block);
	pthread_mutex_unlock(&(g_main_mutex));
}
