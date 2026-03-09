#include "../includes/galloc.h"

void	free(void *ptr)
{
	ft_printf("free\n");
	pthread_mutex_lock(&(g_main_mutex));
	ft_printf("lock mutex free\n");
	ft_printf("free after\n");
	if (!ptr)
	{
		ft_printf("free 0.5\n");
		ft_printf("unlcok mutex\n");
		pthread_mutex_unlock(&(g_main_mutex));
		ft_printf("free 1\n");
		return ;
	}
	ft_printf("free 2\n");
	//ft_printf("%p\n", ptr);
	t_block	*block = (t_block *)((char *)ptr - sizeof(t_block));
	t_header *header = find_header_from_block(block);
	ft_printf("free 3\n");
	if (!header)
	{
		debug_mode(block, "FREE", 0);
		show_mallocs();
		write(1, "free(): invalid pointer\n", 24);
		pthread_mutex_unlock(&(g_main_mutex));
		ft_printf("free 4\n");
		return ;
	}
	block->state = FREE;
	ft_printf("free 5\n");
	defragment_header(&block);
	ft_printf("free 6\n");
	if (get_last_block(header->blocks) == block \
		&& header->blocks->state == FREE) {
		remove_header(header);
		pthread_mutex_unlock(&(g_main_mutex));
		ft_printf("free 7\n");
		show_mallocs();
		return ;
	}
	else if (!block->next && block->prev) {
		header->current_size -= block->size;
		current_allocs_size(FREE, block->size);
		block->prev->next = NULL;
	}
	ft_printf("free 8\n");
	debug_mode(block, "FREE", 0);
	block->mem_size = block->size - sizeof(t_block);
	ft_printf("free 9\n");
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
