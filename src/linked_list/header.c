#include "../../includes/galloc.h"

t_header	*create_header_node(size_t size)
{
	t_header	*node = NULL;
	int			type = get_type_header(size);
	size_t		total_size = get_size_header(size);

	node = get_mmap_region(total_size);
	if (node == MAP_FAILED)
		return NULL;
	current_allocs_size(ASIGNED, sizeof(t_header));

	node->size = total_size;
	node->current_size = sizeof(t_header);
	node->type = type;
	node->blocks = NULL;
	node->next = NULL;
	node->prev = get_last_header(get_main_header());
	if (!get_main_header())
		set_main_header(node);
	else
		node->prev->next = node;
	return node;
}

// check if is avalible space in the blocks or can create a new block with enough space
int	check_header_blocks_size(size_t size, t_header *header)
{
	t_block	*block = header->blocks;
	size_t blocks_size = 0; // counter of total size of blocks
	size_t total_size = 0;

	while (block)
	{
		if (block->state == FREE \
			&& block->size > size)
			return 1;
		blocks_size += block->size;
		block = block->next;
	}
	if (header->size - header->current_size > blocks_size)
		total_size = header->size - header->current_size - blocks_size;
	return (total_size > size + sizeof(t_block))? 1 : 0;
}

// get_block_from_header comprobar si esto esta bien
t_header	*get_header_node(size_t size)
{
	t_header *header = get_main_header();
	while (header)
	{
		// type 3 need his exclusive header
		if (header->type == get_type_header(size) \
			&& get_type_header(size) != LARGE \
			&& header->size - header->current_size  > size + sizeof(t_block) \
			&& check_header_blocks_size(size, header))
		{

			// need check here if is good spot incluiding padding
			return header;
		}
		header = header->next;
	}

	if (!header)
		header = create_header_node(size);

	return header;
}

t_block	*add_block_to_header(size_t size, t_header *header)
{
	t_block	*block = NULL;

	if (!header)
		return NULL;
	if (!header->blocks)
	{
		header->blocks = create_block_node(size, header);
		return header->blocks;
	}
	block = create_block_node(size, header);
	t_block *tmp_block =  get_last_block(header->blocks);

	if (tmp_block != block)
	{
		block->prev = tmp_block;
		tmp_block->next = block;
	}

	//block->prev = get_last_block(header->blocks);
	//block->prev->next = block;
	return block;
}

t_block	*get_block_from_header(size_t size, t_header *header)
{
	t_block	*block = header->blocks;

	while(block)//while(block && block->next)
	{
		// 15 is max padding needed in address for align memory
		if (block->state == FREE \
			&& block->size >= size + sizeof(t_block) \
			&& header->size > header->current_size + size + sizeof(t_block) + 15)
		{
			return block;
		}
		block = block->next;
	}

	if (!block)
		block = add_block_to_header(size, header); // tiene sentido?

	// block = add_last_block_to_header();
	return block;
}
