#include "../includes/galloc.h"
/*
	MMAP:
		return: In error mmap reeturn MAP_FAILED
		the first argument of mmap will be NULL \
		if is the first header or header->type == LARGER
*/
void	*get_mmap_region(size_t header_total_size)
{
	t_header *header = get_main_header();
	while (header)
	{
		if (header->type != LARGE)
			return mmap(header, header_total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
		header = header->next;
	}

	return mmap(NULL, header_total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
}

/*
 	DEFRAMENT HEADER
	BEFORE:
		BLOCK1(state: FREE, size 100)->BLOCK2(state: FREE, size 100)->BLOCK3(state: ASIG, size 100)
	AFTER:
		BLOCK1(state: FREE, size 200)->BLOCK2(state: ASIG, size 100)
	merge 2 or 3 blocks in only 1 block
*/

void	defragment_header(t_block **block_src)
{
	t_block	*block = *block_src;
	if (block->prev && block->prev->state == FREE)
	{
		block->prev->size += block->size;
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
		block = block->prev;
	}
	if (block->next && block->next->state == FREE)
	{
		block->size += block->next->size;
		if (block->next->next)
			block->next->next->prev = block;
		block->next = block->next->next;
	}
	block->mem = (t_block *)((uintptr_t)block + sizeof(t_block));
	*block_src = block;
}

/*
 	DEFRAMENT BLOCK
	BEFORE:
		BLOCK1(state: FREE, size 100)->BLOCK2(state: ASIG, size 100)
	AFTER:
		BLOCK1(state: ASIG, size 50)->BLOCK2(state: FREE, size 50)->BLOCK3(state: ASIG, size 100)

*/
void	split_block(t_block *block, size_t size)
{
	// Check if is enough space for the alignment of the memory
	if (block->size - (size + sizeof(t_block)) < 64)
		return ;
	size_t padding = 16 - (size % 16);
	block->mem_size = size + padding;
	// create_block_from_ptr arguments:
	//		-1: subtract the memory from the first block for the second block
	// 		-2: move the pointer out of his own memory
	t_block	*new_block = create_block_from_ptr(block->size - (block->mem_size + sizeof(t_block)), \
		(t_block*)((uintptr_t)block + sizeof(t_block) + size));
	block->size -= new_block->size;


	// connect the new block with the others
	if (block->next)
	{
		block->next->prev = new_block;
		new_block->next = block->next;
	}
	new_block->prev = block;
	block->next = new_block;
}
