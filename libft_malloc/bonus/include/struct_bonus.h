#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

typedef struct s_block
{
	size_t			size;
	size_t			aligned_size;
	struct s_block	*prev;
	struct s_block	*next;
}	t_block;

typedef struct s_heap_group
{
	size_t				aligned_size;
	t_block				*alloc_block;
	t_block				*free_block;
	struct s_heap_group	*prev;
	struct s_heap_group	*next;
}	t_heap_group;

typedef struct s_heap
{
	t_heap_group	*tiny_heap;
	t_heap_group	*small_heap;
	t_heap_group	*large_heap;
}	t_heap;

#endif
