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
	block->mem_size = 0; // debug
	//
	block->state = FREE;
	defragment_header(block);
	printf("block free mem size %lu\n", block->mem_size); // debug
	assert(block->mem_size < 100000); // debug
	if (get_last_block(header->blocks) == header->blocks \
		&& header->blocks->state == FREE)
		remove_header(header);
	else if (!block->next && block->prev) {
		header->current_size -= block->size;
		current_allocs_size(FREE, block->size);
		printf("freeeeee not next ----------------------------\n");
		block->prev->next = NULL;
	}
	//block->mem_size = 0; // debug
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
