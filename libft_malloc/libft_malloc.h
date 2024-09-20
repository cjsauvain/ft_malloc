#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>

# define TINY_BLOCK 64
# define SMALL_BLOCK 512
# define TINY_HEAP 4 * sysconf(_SC_PAGESIZE)
# define SMALL_HEAP 16 * sysconf(_SC_PAGESIZE)


# define align_mem(size) ((size + (sizeof(void *) - 1)) & ~(sizeof(void *) - 1))

typedef struct s_heap	t_heap;

extern t_heap	*g_heap;

typedef struct s_block
{
	size_t			size;
	size_t			aligned_size;
	struct s_block	*prev;
	struct s_block	*next;
} t_block;

typedef struct s_heap
{
	size_t			size;
	size_t			aligned_size;
	t_block			*alloc_block;
	t_block			*free_block;
	struct s_heap	*prev;
	struct s_heap	*next;
} t_heap;

void	*ft_malloc(size_t size);
void	allocate_new_heap(size_t size);
int		count_heap(void);
int		check_heap_state(size_t size);
void	select_heap(size_t size);
void	*get_avail_block(size_t size);
void	ft_free(void *ptr);
void	*ft_realloc(void *ptr, size_t size);

#endif
