#include "../../includes/galloc.h"

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
