#include "../../includes/galloc.h"

t_header	*create_header_node(size_t size)
{
	printf("creating header addres global:%p\n", g_main_header);
	t_header	*node = NULL;
	int			type = get_type_header(size);
	size_t		total_size = get_size_header(size);

	//printf("mmap: %p\n", (type == 3)?g_main_header:NULL);
	node = mmap((type == 3)?NULL:g_main_header, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (!node)
		return NULL;
	//printf("header total size: %lu\ntype:%i\n", total_size, type);
	node->size = total_size;
	node->current_size = 0;
	node->type = type;
	node->blocks = NULL;
	node->next = NULL;
	node->prev = get_last_header(g_main_header);
	if (!g_main_header)
		g_main_header = node;
	else
		node->prev->next = node;
	//create_block_pading(node);
	//printf("KLK type: %i header->type: %i\n", type, node->type);
	return node;
}

// get_block_from_header comprobar si esto esta bien
t_header	*get_header_node(size_t size)
{
	t_header *header = g_main_header;
	if (header)
		printf("block address: %p\n", header->blocks);
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
		if ( header->size - header->current_size  > size + sizeof(t_block) \
			&& header->type == get_type_header(size) && get_type_header(size) != 3)
		{
			printf("header founded\n");
			// need check here if is good spot incluiding padding
			return header;
		}
		header = header->next;
	}
	printf("header no encontrado\n");
	if (!header)
		header = create_header_node(size);
	//printf("KLK header->type: %i\n", header->type);
	return header;
}

t_header	*get_header_node_from_context(size_t size, t_header *header)
{
	if (!header)
		return NULL;
	while (header)
	{
		if (header->size - header->current_size > size \
			&& header->type == get_type_header(size))
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

t_header	*get_last_header(t_header *list)
{
	t_header *tmp_node = NULL;

	if (!list)
		return NULL;
	tmp_node = list;
	while (tmp_node->next)
		tmp_node = tmp_node->next;
	return tmp_node;
}

t_header	*get_main_header(void)
{
	t_header	*ptr = g_main_header;
	return ptr;
}

t_block	*add_block_to_header(size_t size, t_header *header)
{
	t_block	*block = NULL;

	if (!header)
		return NULL;
	if (!header->blocks)
	{
		header->blocks = create_block_node(size, header);
		printf("hola!\n");
		return header->blocks;
	}
	block = create_block_node(size, header);
	t_block *tmp_block =  get_last_block(header->blocks);
	printf("hola? last %p new %p\n", tmp_block, block);
	if (tmp_block != block)
	{
		printf("hola!\n");
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
		printf("block iter\n");
		if (block->state == FREE && block->size > size + sizeof(t_block)) //
		{
			printf("block founded");
			return block;
		}
		block = block->next;
	}
	printf("creating block\n");
	if (!block)
		block = add_block_to_header(size, header); // tiene sentido?
	//printf("LKL header->type: %i\n", header->type);
	// block = add_last_block_to_header();
	return block;
}

void	show_mallocs(void)
{
	t_header	*header = g_main_header;
	t_block		*block = NULL;

	while (header)
	{
		printf("\nheader: %p\n\tsize: %lu\n\tcurrent: %lu\n\ttype: %i\n\n", header, header->size, header->current_size, header->type);
		block = header->blocks;
		while (block)
		{
			printf("\tblock: %p\n\tmem: %p\n\tsize: %lu\n\tstate: %i\n", block, block->mem, block->size, block->state);
			block = block->next;
			printf("\n");
		}
		printf("\n");
		header = header->next;
	}
}
