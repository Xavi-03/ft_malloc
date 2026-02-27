#include "../includes/galloc.h"

void	gfree(void *ptr)
{
	pthread_mutex_lock(&(g_main_mutex));
	if (!ptr)
	{
		write(1, "free(): invalid pointer\n", 24);
		pthread_mutex_unlock(&(g_main_mutex));
		return ;
	}

	t_block	*block = (t_block *)((char *)ptr - sizeof(t_block));

	t_header *header = find_header_from_block(block);
	if (!header)
	{
		printf("free(): invalid pointer\n");
		pthread_mutex_unlock(&(g_main_mutex));
		return ;
	}

	current_allocs_size(FREE, block->size - sizeof(t_block));
	block->state = FREE;
	header->current_size -= block->size - sizeof(t_block);
	defragment_header(header, block);

	if (get_last_block(header->blocks) == header->blocks \
		&& header->blocks->state == FREE)
		remove_header(header);

	debug_mode(block, "FREE", 0);
	pthread_mutex_unlock(&(g_main_mutex));
}

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
