#include "../../includes/galloc.h"
#include <stdint.h>

t_header	*create_header_node(size_t size)
{
	t_header	*node = NULL;
	int			type = get_type_header(size);
	size_t		total_size = get_size_header(size);
	node = get_mmap_region(total_size);
	if (node == MAP_FAILED) // mmap failed
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

// check if is avalible space in the free blocks
int	check_free_blocks_size(size_t size, t_header *header)
{
	t_block	*block = header->blocks;
	size_t padding = (size % 16)? 16 - size % 16 : 0;
	while (block)
	{
		if (block->state == FREE \
			&& block->size >= size + sizeof(t_block) + padding) {
			return 1;
		}
		block = block->next;
	}
	return 0;
}

t_header	*get_header_node(size_t size)
{
	size_t padding = (size % 16)? 16 - (size % 16): 0;
	t_header *header = get_main_header();
	if (get_type_header(size) == LARGE)
		return create_header_node(size);
	while (header)
	{
		if ((header->type == get_type_header(size) \
			&& get_type_header(size) != LARGE \
			&& header->size - header->current_size  >= size + sizeof(t_block) + padding) \
			|| (check_free_blocks_size(size, header)
				&& header->type == get_type_header(size))) {
			if (header->size < header->current_size + size + sizeof(t_block) + padding) {
				header = header->next;
				continue;
			}
			return header;
		}
		header = header->next;
	}
	return (header) ? header : create_header_node(size);
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
	return block;
}

t_block	*get_block_from_header(size_t size, t_header *header)
{
	t_block	*block = header->blocks;
	uint8_t	padding = (size % 16)? 16 - (size % 16) : 0;
	while(block)
	{
		if (block->state == FREE && block->size >= size + sizeof(t_block) + padding)
			return block;
		block = block->next;
	}
	if (!block)
		block = add_block_to_header(size, header); // tiene sentido?
	return block;
}
