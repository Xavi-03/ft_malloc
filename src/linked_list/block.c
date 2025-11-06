#include "../../includes/galloc.h"
//(void *)(((uintptr_t)header_mem + 15) & ~(uintptr_t)0xF)
// (void *)((char *)node->mem + ((uintptr_t)node % 16 == 0)? (uintptr_t)node % 16 : 16);
t_block	*create_block_node(size_t size, t_header *header_mem)
{
	//printf("creating block\n");
	current_allocs_size(ASIGNED, sizeof(t_block));
	t_block	*node = (t_block *)header_mem;
	node = (t_block *)((char *)node + sizeof(t_block) + header_mem->current_size);
	node = (void *)(((uintptr_t)node + 15) & ~(uintptr_t)0xF);
	//printf("sizes header:%lu, block:%lu\n", sizeof(t_header), sizeof(t_block));
	node->mem = (void *)((char *)node + (size_t)sizeof(t_block));
	//node->mem = (void *)(((uintptr_t)node->mem + 15) & ~(uintptr_t)0xF);
	printf("mem pointer in block --- %p\n", node->mem);
	node->size = size + (size_t)sizeof(t_block);
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
	header->current_size = header->current_size + size + sizeof(t_block);
	return block->mem;
}//(void*)((char*)block + sizeof(t_block));

t_block	*get_last_block(t_block *list)
{
	t_block *tmp_node = NULL;

	if (!list)
		return NULL;
	tmp_node = list;
	while (tmp_node->next)
	{
		//printf("a\n");
		tmp_node = tmp_node->next;
	}
	return tmp_node;
}

t_header	*find_header_from_block(t_block *block)
{
	t_header	*header = get_main_header();
	t_block		*tmp_block;

	while (header)
	{
		tmp_block = header->blocks;
		//printf("header address %p\n", header);
		while (tmp_block)
		{
			printf("comparation %p %p\n", tmp_block, block);
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
