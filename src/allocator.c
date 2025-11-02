#include "../includes/galloc.h"

/*void *alloc_category(size_t size) {
	t_header *node = NULL;

	node = get_header_node(1);
	node = get_header_node(500);
	node = get_header_node(2000);
	node = get_header_node(6000);
	node = get_header_node(20000);

	t_header *main = get_main_header();
	int i = 0;
	t_header *tmp = get_main_header();
	tmp->type = 100;
	while (main)
	{
		printf("node:%i %p\n type:%i\n size:%zu\n current_size:%zu\n\n", ++i, main, main->type, main->size, main->current_size);
		main = main->next;
	}
	tmp->type = 300;
	main = get_main_header();
	i = 0;
	while (main)
	{
		printf("node:%i %p\n type:%i\n size:%zu\n current_size:%zu\n\n", ++i, main, main->type, main->size, main->current_size);
		main = main->next;
	}
	void *ptr = NULL;
	return ptr;
	return 0;
}*/
