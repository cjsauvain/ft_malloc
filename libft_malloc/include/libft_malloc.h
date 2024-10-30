#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"


# define align_mem(size) ((size + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1))

# define TINY_BLOCK 64
# define SMALL_BLOCK 512
# define TINY_HEAP 4 * sysconf(_SC_PAGESIZE)
# define SMALL_HEAP 16 * sysconf(_SC_PAGESIZE)

#define URED "\e[4;31m"
#define BMAG "\e[1;35m"
#define reset "\e[0m"

typedef struct s_heap	t_heap;

extern t_heap	g_heap;

typedef struct s_block
{
	size_t			size;
	size_t			aligned_size;
	struct s_block	*prev;
	struct s_block	*next;
} t_block;

typedef struct s_heap_group
{
	size_t				aligned_size;
	t_block				*alloc_block;
	t_block				*free_block;
	struct s_heap_group	*prev;
	struct s_heap_group	*next;
} t_heap_group;

typedef struct s_heap
{
	t_heap_group	*tiny_heap;
	t_heap_group	*small_heap;
	t_heap_group	*large_heap;
} t_heap;

void			*ft_malloc(size_t size);
t_heap_group	*allocate_heap(size_t size, int mode);
int				count_heap(void);
int				check_heap_state(size_t size);
t_heap_group	*check_heap_left(size_t size);
t_heap_group	*select_heap(size_t size);
void			*get_avail_block(t_heap_group *heap, size_t size);
void			ft_free(void *ptr);
void			*ft_realloc(void *ptr, size_t size);
void		 	show_alloc_mem(void);
t_heap_group	*find_heap(t_block *, int i);
t_heap_group	*merge_heaps(t_heap_group *heap_pos, t_heap_group *new_heap, size_t alloc_size);
t_block			*shrink_alloc_block(t_heap_group *heap, t_block *ptr_block, size_t realloc_size);
t_block			*shrink_free_block(t_heap_group *heap, t_block *ptr_block, t_block *realloc_block, size_t realloc_size);
void			*extend_block(t_heap_group *heap, t_block *ptr_block, size_t realloc_size);
t_block			*delete_block(t_block *block, size_t size, int merge_req);
t_block			*add_alloc_block(t_heap_group *heap, t_block *free_block, size_t size);
void			add_free_block(t_heap_group *heap, t_block *block);
t_heap_group	*add_heap(size_t size);
t_heap_group	*allocate_heap(size_t size, int mode);
int				get_new_index(int index, int i);
void			initialize_new_heap(t_heap_group *new_heap, size_t alloc_size);
size_t			get_alloc_size(size_t size);
t_heap_group	*create_heap(size_t size);

#endif
