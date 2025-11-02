#include "../includes/galloc.h"



void *galloc(size_t size) {

	t_header	*header = get_header_node(size);
	if (!header)
		return NULL;
	t_block *block = get_block_from_header(size, header);
	void *ptr = asign_block(size, block, header);
	//printf("header: %p header type: %i\n\tblock:\t%p\n\tptr:\t%p \n\n", header, header->type, block, ptr);
	return ptr;


		//void *ptr;
	//ptr = alloc_category(size);
	//return ptr;
}
