#include "../includes/galloc.h"



void *galloc(size_t size) {

	pthread_mutex_lock(&(g_main_mutex));
	t_header	*header = get_header_node(size);
	if (!header)
		return NULL;

	t_block *block = get_block_from_header(size, header);
	void *ptr = asign_block(size, block, header);
	current_allocs_size(ASIGNED, size);
	//printf("header: %p header type: %i\n\tblock:\t%p\n\tptr:\t%p \n\n", header, header->type, block, ptr);
	pthread_mutex_unlock(&(g_main_mutex));
	//printf("ptr returned: %p\n", ptr);
	return ptr;

		//void *ptr;
	//ptr = alloc_category(size);
	//return ptr;

	// check if not more memory allocated and use munmap of all arena
}
