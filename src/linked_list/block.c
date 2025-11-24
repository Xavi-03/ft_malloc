#include "../../includes/galloc.h"
//(void *)(((uintptr_t)header_mem + 15) & ~(uintptr_t)0xF)
// (void *)((char *)node->mem + ((uintptr_t)node % 16 == 0)? (uintptr_t)node % 16 : 16);
t_block	*create_block_node(size_t size, t_header *header_mem)
{
	//current_allocs_size(ASIGNED, sizeof(t_block));
	t_block	*node = (t_block *)header_mem;
	node = (t_block *)((char *)node + sizeof(t_block) + header_mem->current_size);
	node = (void *)(((uintptr_t)node + 15) & ~(uintptr_t)0xF);
	node->mem = (void *)((char *)node + (size_t)sizeof(t_block));
	//node->mem = (void *)(((uintptr_t)node->mem + 15) & ~(uintptr_t)0xF);
	node->size = size + (size_t)sizeof(t_block);
	node->state = FREE;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

t_block	*create_block_from_ptr(size_t size, void *ptr)
{
	//current_allocs_size(ASIGNED, sizeof(t_block));
	t_block	*node = (t_block *)ptr;
	node = (void *)(((uintptr_t)node + 15) & ~(uintptr_t)0xF);
	node->mem = (void *)((char *)node + (size_t)sizeof(t_block));
	//node->mem = (void *)(((uintptr_t)node->mem + 15) & ~(uintptr_t)0xF);
	node->size = size;
	node->state = FREE;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void	*asign_block(size_t size, t_block *block, t_header *header)
{
	if (!block)
		return NULL;
	if (block->size < size + sizeof(t_block))
		return NULL;
	block->size = size + sizeof(t_block);
	block->state = ASIGNED;
	header->current_size += size + sizeof(t_block);
	current_allocs_size(ASIGNED, size + sizeof(t_block));
	return block->mem;
}//(void*)((char*)block + sizeof(t_block));

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

/*t_block	*init_block_pading(t_header *header)
{
	if (header->blocks)
		return NULL;
	t_block *block = (void *)((char *)header + sizeof(t_header *));
	block->mem = NULL;
	block->size = (size_t)block % 16;
	}*/
