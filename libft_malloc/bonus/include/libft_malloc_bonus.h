#ifndef LIBFT_MALLOC_BONUS_H
# define LIBFT_MALLOC_BONUS_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include "struct_bonus.h"
# include "defines_bonus.h"
# include "libft.h"

//GLOBAL VARIABLES
typedef struct s_heap	t_heap;
extern t_heap	g_heap;
extern pthread_mutex_t	g_mutex;


//FUNCTIONS
void			*ft_malloc(size_t size);
int				count_heap(void);
int				check_heap_state(size_t size);
t_heap_group	*check_heap_left(size_t size);
t_heap_group	*select_heap(size_t size);
void			*get_avail_block(t_heap_group *heap, size_t size);
void			ft_free(void *ptr);
void			*ft_realloc(void *ptr, size_t size);
void		 	show_alloc_mem_ex(char *heap_str);
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
