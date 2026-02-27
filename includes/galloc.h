#ifndef GALLOC_H
# define GALLOC_H

# include <stddef.h>
# include <unistd.h> // sysconf
# include <sys/mman.h> // mmap munmap
//# include <stdbool.h> // boolean
# include <sys/resource.h> // getrlimit
# include <stdint.h> // uintptr_t
# include <pthread.h>
# include "../libft/libft.h"

# include <stdio.h> /// debug
# include <stdlib.h>

// Size limits of blocks
# define N 128
# define M 1024

#ifndef SHOW_MALLOC
	# define SHOW_MALLOC 0
#endif

#ifndef SHOW_MALLOC_INFO
	# define SHOW_MALLOC_INFO 0
#endif

#ifndef SHOW_DUMP
	# define SHOW_DUMP 0
#endif


/*# define TINY 1
# define SMALL 2
# define LARGE 3


# define GET_MEMORY_SIZE 0
# define FREE 1
# define ASIGNED 2*/
// Headers Sizes
typedef enum e_type {
	TINY,
	SMALL,
	LARGE
} t_type;

// Blocks States
typedef enum e_state {
	GET_MEMORY_SIZE,
	FREE,
	ASIGNED
} t_state;

typedef struct	s_header {
	size_t				size;
	size_t				current_size;
	t_type				type;
	struct	s_block		*blocks;
	struct	s_header	*next;
	struct	s_header	*prev;
}	t_header;

typedef struct	s_block {
	void			*mem;
	size_t			size;
	uint64_t		real_size;
	t_state			state;
	struct	s_block	*next;
	struct	s_block	*prev;
}	t_block;

static pthread_mutex_t g_main_mutex = PTHREAD_MUTEX_INITIALIZER;
static t_header *g_main_header = NULL;


// src/galloc.c
void *galloc(size_t size);

// src/gfree.c
void	gfree(void *ptr);
void	remove_header(t_header *header);

// src/realloc.c
void	*regalloc(void *ptr, size_t size);

// src/allocator.c
void *alloc_category(size_t size);

// src/global_managment.c
t_header	*get_main_header(void);
void		set_main_header(void *ptr);

// src/memoty_managment.c
void	*get_mmap_region(size_t header_total_size);
void	defragment_header(t_header *header, t_block *block);
void	split_block(t_block *block, size_t size);

// src/allocs_limits.c


// src/debbug
void	show_mallocs(void);
size_t	current_allocs_size(int state, size_t size);
void	show_alloc_mem_ex(void);
void	show_dump(t_block *block);
void	debug_mode(t_block *block, char *type);

// src/utils.c
t_type		get_type_header(size_t size);
int			get_size_header(size_t size);

// src/linked_list/header.c
t_header	*create_header_node(size_t size);
t_header	*get_header_node(size_t size);
void 		*get_header_mem(size_t size, t_header *header);
t_block		*add_block_to_header(size_t size, t_header *header);
t_block		*get_block_from_header(size_t size, t_header *header);
int			check_header_blocks_size(size_t size, t_header *header);

// src/linked_list/block.c
t_block		*create_block_node(size_t size, t_header *header_mem);
t_block		*create_block_from_ptr(size_t size, void *ptr);
void		*asign_block(size_t size, t_block *block, t_header *header);
t_header	*find_header_from_block(t_block *block);

// src/linked_list/linked_list_utils.c
t_header	*get_last_header(t_header *list);
t_block		*get_last_block(t_block *list);

#endif

//que pasa si tengo un espacio
