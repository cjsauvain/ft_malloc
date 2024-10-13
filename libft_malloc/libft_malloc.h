#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/libft.h"


# define align_mem(size) ((size + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1))

# define TINY_BLOCK 64
# define SMALL_BLOCK 512
# define TINY_HEAP 4 * sysconf(_SC_PAGESIZE)
# define SMALL_HEAP 16 * sysconf(_SC_PAGESIZE)

typedef struct s_heap	t_heap;

extern t_heap	g_heap;

typedef struct s_block
{
	int				heap_index;
	size_t			size;
	size_t			aligned_size;
	struct s_block	*prev;
	struct s_block	*next;
} t_block;

typedef struct s_heap_group
{
	int					index;
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
t_heap_group	*find_heap(int heap_index, int i);

#endif
