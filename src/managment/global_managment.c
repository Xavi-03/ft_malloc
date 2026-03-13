#include "../../includes/galloc.h"

t_header	*get_main_header(void)
{
	t_header	*ptr = g_main_header;
	return ptr;
}

void	set_main_header(void *ptr)
{
	g_main_header = ptr;
}
