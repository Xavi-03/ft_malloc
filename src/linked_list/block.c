#include "../../includes/galloc.h"
//(void *)(((uintptr_t)header_mem + 15) & ~(uintptr_t)0xF)
// (void *)((char *)node->mem + ((uintptr_t)node % 16 == 0)? (uintptr_t)node % 16 : 16);
t_block	*create_block_node(size_t size, t_header *header_mem)
{
	t_header *header = header_mem;
	uint8_t padding = 16 - (size % 16);
	padding = (padding == 16) ? 0 : padding;

	t_block *node = (t_block *)((uintptr_t)header_mem + header_mem->current_size);
	node->mem = (void *)((uintptr_t)node + (size_t)sizeof(t_block));

	node->mem_size = size + padding;
	node->size = size + (size_t)sizeof(t_block) + padding;
	// + padding;
	node->state = FREE;
	node->next = NULL;
	node->prev = NULL;
	header->current_size += node->size;
	current_allocs_size(ASIGNED, node->size);
	return node;
}

t_block	*create_block_from_ptr(size_t size, void *ptr)
{
	t_block	*node = (void *)(((uintptr_t)ptr + 15) & ~(uintptr_t)0xF);
	node->mem = (void *)((char *)node + (size_t)sizeof(t_block) );
	node->size = size;
	node->mem_size = size - sizeof(t_block);

	node->state = FREE;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void	*asign_block(size_t size, t_block *block)
{
	if (!block)
		return NULL;
	if (block->size < size + sizeof(t_block))
		return NULL;

	block->state = ASIGNED;
	block->mem_size = block->size - sizeof(t_block);
	return block->mem;
}

t_header	*find_header_from_block(t_block *block)
{
	t_header	*header = get_main_header();
	t_block		*tmp_block;

	while (header)
	{
		tmp_block = header->blocks;
		while (tmp_block)
		{
			if (tmp_block == block)
				return header;
			tmp_block = tmp_block->next;
		}
		header = header->next;
	}

	return header;
}
