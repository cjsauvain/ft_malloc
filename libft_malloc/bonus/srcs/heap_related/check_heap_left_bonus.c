#include "libft_malloc_bonus.h"

static size_t	check_available_blocks(t_block *heap_free, size_t size)
{
	while (heap_free)
	{
		if (heap_free->size >= size)
			return 1;
		heap_free = heap_free->next;
	}
	return 0;
}

t_heap_group	*check_heap_left(size_t size)
{
	t_heap_group	*heap;

	if (size > SMALL_BLOCK)
		return NULL;
	heap = select_heap(size);
	while (heap)
	{
		if (check_available_blocks(heap->free_block, size))
			return heap;
		heap = heap->next;
	}
	return NULL;
}
