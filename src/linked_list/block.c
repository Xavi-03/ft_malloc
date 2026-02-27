#include "../../includes/galloc.h"
//(void *)(((uintptr_t)header_mem + 15) & ~(uintptr_t)0xF)
// (void *)((char *)node->mem + ((uintptr_t)node % 16 == 0)? (uintptr_t)node % 16 : 16);
t_block	*create_block_node(size_t size, t_header *header_mem)
{

//	printf("--- size t_block %lu uint64_t size %lu\n", sizeof(t_block), sizeof(uint64_t));
	t_block *node = (t_block *)((uintptr_t)header_mem + (uintptr_t)(sizeof(t_block) + header_mem->current_size));
	uint64_t padding = 16 - (size % 16);
	//uint8_t	padding = (uintptr_t)((((uintptr_t)node + 15) & ~(uintptr_t)0xF) - (uintptr_t)node);
	//printf("size %lu - padding %lu - total_size %lu - x16 %lu\n", size, padding, size + padding, (size + padding) % 16);
//	printf("node is this aligned? %p\n", node);
	node = (t_block *)((((uintptr_t)node + 15) & ~(uintptr_t)0xF));
//	printf("node is this aligned? %p\n", node);


	node->mem = (void *)((uintptr_t)node + (size_t)sizeof(t_block));
//	printf("node->mem is this aligned? %p\n\n", node->mem);


	//node->mem = (void *)(((uintptr_t)node->mem + 15) & ~(uintptr_t)0xF);
	node->mem_size = size + padding;
	node->size = size + (size_t)sizeof(t_block) + padding;// + padding;
	node->state = FREE;
	node->next = NULL;
	node->prev = NULL;
//	printf("size %lu\n\n\n\n\n", node->size);
	return node;
}

t_block	*create_block_from_ptr(size_t size, void *ptr)
{
	//current_allocs_size(ASIGNED, sizeof(t_block));
	t_block	*node = (void *)(((uintptr_t)ptr + 15) & ~(uintptr_t)0xF);
	node->mem = (void *)((char *)node + (size_t)sizeof(t_block) );// + padding);
	//node->mem = (void *)(((uintptr_t)node->mem + 15) & ~(uintptr_t)0xF);
	node->size = size;// + padding;
	node->mem_size = size - sizeof(t_block); //(size - sizeof(t_block));// + padding;
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
	//block->size = size + sizeof(t_block);
	block->state = ASIGNED;
	header->current_size += block->size;
	current_allocs_size(ASIGNED, block->size);//size + sizeof(t_block));
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
