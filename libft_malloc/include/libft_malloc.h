#ifndef LIBFT_MALLOC_H
# define LIBFT_MALLOC_H

# include <sys/mman.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include "struct.h"
# include "defines.h"
# include "libft.h"


typedef struct s_heap	t_heap;

//GLOBAL VARIABLES
extern t_heap			g_heap;
extern pthread_mutex_t	g_mutex;


//FUNCTIONS
void			*malloc(size_t size);
int				count_heap(void);
int				check_heap_state(size_t size);
t_heap_group	*check_heap_left(size_t size);
t_heap_group	*select_heap(size_t size);
void			*get_avail_block(t_heap_group *heap, size_t size);
void			free(void *ptr);
void			*realloc(void *ptr, size_t size);
void			show_mem_hexdump(char *heap_str);
void			show_alloc_mem(void);
t_heap_group	*find_heap(t_block *block, int i);
t_heap_group	*merge_heaps(t_heap_group *heap_pos, t_heap_group *new_heap, \
					size_t alloc_size);
void			add_heap_pos_free_blocks(t_heap_group *heap_pos, \
					t_heap_group *new_heap, size_t alloc_size);
void			add_new_heap_free_blocks(t_heap_group *heap_pos, \
					size_t alloc_size);
t_block			*shrink_alloc_block(t_heap_group *heap, t_block *ptr_block, \
					size_t realloc_size);
t_block			*shrink_free_block(t_heap_group *heap, t_block *ptr_block, \
					t_block *realloc_block, size_t realloc_size);
void			*extend_block(t_heap_group *heap, t_block *ptr_block, \
					size_t realloc_size);
t_block			*delete_block(t_block *block, size_t size, int merge_req);
t_block			*delete_whole_block(t_block *block, int merge_req);
t_block			*delete_partially(t_block *block, size_t size);
t_block			*add_alloc_block(t_heap_group *heap, t_block *free_block);
void			add_free_block(t_heap_group *heap, t_block *block);
t_heap_group	*add_heap(size_t size);
t_heap_group	*allocate_heap(size_t size, int mode);
int				get_new_index(int index, int i);
void			initialize_new_heap(t_heap_group *new_heap, \
					size_t alloc_size);
size_t			get_heap_group(size_t size);
t_heap_group	*create_heap(size_t size);
t_heap_group	*find_heap(t_block *block, int i);
void			initialize_new_heap(t_heap_group *new_heap, \
					size_t alloc_size);
void			display_hexa_format(t_heap_group *heap, \
					t_block *alloc_block);

#endif
