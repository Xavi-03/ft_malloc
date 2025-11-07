#include "../../includes/galloc.h"

void	*get_mmap_region(int header_type, size_t header_total_size)
{
	t_header *header = get_main_header();
	if (!header || header_type == 3)
		return mmap(NULL, header_total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	else
	{
		while (header)
		{
			if (header->type != 3)
				return mmap(header, header_total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
			header = header->next;
		}
	}
	return NULL;
}

t_header	*create_header_node(size_t size)
{
	//printf("creating header addres global:%p\n", g_main_header);
	t_header	*node = NULL;
	int			type = get_type_header(size);
	size_t		total_size = get_size_header(size);

	node = get_mmap_region(type, total_size);
	//node = mmap((type == 3)?NULL:g_main_header, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!node)
		return NULL;
	current_allocs_size(ASIGNED, sizeof(t_header));
	//printf("header total size: %lu\ntype:%i\n", total_size, type);
	node->size = total_size;
	node->current_size = sizeof(t_header);
	node->type = type;
	node->blocks = NULL;
	node->next = NULL;
	node->prev = get_last_header(g_main_header);
	if (!g_main_header)
		g_main_header = node;
	else
		node->prev->next = node;
	return node;
}

// check if is avalible space in the blocks or can create a new block with enough space
int	check_header_blocks_size(size_t size, t_header *header)
{
	t_block	*block = header->blocks;
	size_t blocks_size = 0; // counter of total size of blocks

	while (block)
	{
		if (block->state == FREE \
			&& block->size > size)
			return 1;
		blocks_size += block->size;
		block = block->next;
	}
	if (header->size - header->current_size - blocks_size > size + sizeof(t_block))
		return 1;
	return 0;
}

// get_block_from_header comprobar si esto esta bien
t_header	*get_header_node(size_t size)
{
	t_header *header = g_main_header;
	//if (header)
		//printf("block address: %p\n", header->blocks);
	if (!header)
	{
		header = create_header_node(size);
		return header;
	}
	//printf("is global %p\n", g_main_header);
	//printf("LKL header->type: %i\n", header->type);
	while (header)
	{
		//printf("header size:%lu type:%i\n", header->size, header->type);
		// type 3 need is exclusive header
		if (header->type == get_type_header(size)\
			&& get_type_header(size) != 3 \
			&& header->size - header->current_size  > size + sizeof(t_block) \
			&& check_header_blocks_size(size, header))
		{
			//printf("header founded\n");
			// need check here if is good spot incluiding padding
			return header;
		}
		header = header->next;
	}
	//printf("header no encontrado\n");
	if (!header)
		header = create_header_node(size);
	//printf("KLK header->type: %i\n", header->type);
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
		//printf("hola!\n");
		return header->blocks;
	}
	block = create_block_node(size, header);
	t_block *tmp_block =  get_last_block(header->blocks);
	//printf("hola? last %p new %p\n", tmp_block, block);
	if (tmp_block != block)
	{
		//printf("hola!\n");
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
	//printf("LKL header->type: %i\n", header->type);
	while(block)//while(block && block->next)
	{
		//printf("block iter\n");
		if (block->state == FREE && block->size > size + sizeof(t_block)) //
		{
			//printf("block founded");
			return block;
		}
		block = block->next;
	}
	//printf("creating block\n");
	if (!block)
		block = add_block_to_header(size, header); // tiene sentido?
	//printf("LKL header->type: %i\n", header->type);
	// block = add_last_block_to_header();
	return block;
}
