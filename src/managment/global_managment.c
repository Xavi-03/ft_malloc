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

pthread_mutex_t	*get_global_mutes(void)
{
	pthread_mutex_t	*ptr = &g_main_mutex;
	return ptr;
}
