#ifndef GALLOC_H
# define GALLOC_H

# include <stddef.h>
# include <unistd.h> // sysconf
# include <sys/mman.h> // mmap munmap
# include <stdbool.h> // boolean
# include <sys/resource.h> // getrlimit
#include <stdint.h> // uintptr_t

# include <stdio.h> /// debug

// Size limits of blocks
# define N 128
# define M 1024

// Headers Sizes
# define TINY 1
# define SMALL 2
# define LARGE 3

// Blocks States
# define FREE 1
# define ASIGNED 2
# define PADDING 3

typedef struct	s_header {
	size_t	size;
	size_t	current_size;
	int		type;
	struct	s_block *blocks;
	struct	s_header *next;
	struct	s_header *prev;
}	t_header;

typedef struct	s_block {
	void	*mem;
	size_t	size;
	int		state;
	struct	s_block *next;
	struct	s_block *prev;
}	t_block;

static t_header *g_main_header = NULL;


// src/galloc.c
void *galloc(size_t size);

// src/allocator.c
void *alloc_category(size_t size);

// src/utils.c
int get_type_header(size_t size);
int get_size_header(size_t size);

// src/linked_list/header.c
t_header	*create_header_node(size_t size);
t_header	*get_last_header(t_header *list);
t_header	*get_main_header(void);
t_header	*get_header_node(size_t size);
t_header	*get_header_node_from_context(size_t size, t_header *header);
void 		*get_header_mem(size_t size, t_header *header);
t_block		*add_block_to_header(size_t size, t_header *header);
t_block		*get_block_from_header(size_t size, t_header *header);
void		show_mallocs(void);

// src/linked_list/block.c
t_block	*create_block_node(size_t size, t_header *header_mem);
void	*asign_block(size_t size, t_block *block, t_header *header);
t_block	*get_last_block(t_block *list);
// src/linked_list/utils.c


#endif

//que pasa si tengo un espacio
