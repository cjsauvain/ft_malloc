#include "libft_malloc_bonus.h"

t_heap_group	*merge_heaps(t_heap_group *heap_pos, t_heap_group *new_heap, \
	size_t alloc_size)
{
	if (heap_pos < new_heap)
	{
		add_new_heap_free_blocks(heap_pos, alloc_size);
		return heap_pos;
	}
	add_heap_pos_free_blocks(heap_pos, new_heap, alloc_size);
	return new_heap;
}
