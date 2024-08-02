#include "ft_malloc.h"

int	count_heap(t_heap *heap)
{
	if (!heap)
		return 0;
	if (heap->prev || heap->next)
		return 2;
	return 1;
}

int	check_heap_state(t_heap *heap, size_t size)
{
	if (!heap)
		return 1;
	if (heap->prev)
		heap = heap->prev;
	else if (count_heap(heap) < 2)
	{
		if (size > TINY_BLOCK && size <= SMALL_BLOCK
			&& heap->size == (size_t)TINY_HEAP)
			return 1;
		if (size < TINY_BLOCK && heap->size == (size_t)SMALL_HEAP)
			return 1;
	}	
	return 0;
}

t_heap	*select_heap(t_heap *heap, size_t size)
{
	if (size <= TINY_BLOCK && heap->size != (size_t)TINY_HEAP)
		return heap->next;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK 
		&& heap->size != (size_t)SMALL_HEAP)
		return heap->next;
	return heap;
}

