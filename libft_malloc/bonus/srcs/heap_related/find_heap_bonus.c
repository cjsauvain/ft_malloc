#include "libft_malloc_bonus.h"

static int	check_if_block_is_allocated(t_heap_group *heap, t_block *block)
{
	t_block	*tmp;

	tmp = heap->alloc_block;
	while (tmp)
	{
		if (tmp == block)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

t_heap_group	*find_heap(t_block *block, int i)
{
	t_heap_group	*heap;

	if (i == 0)
		heap = g_heap.tiny_heap;
	else if (i == 1)
		heap = g_heap.small_heap;
	else
		heap = g_heap.large_heap;
	while (heap)
	{
		if (check_if_block_is_allocated(heap, block))
			break;
		heap = heap->next;
	}
	if (i == 2 && !heap)
		return NULL;
	else if (!heap)
		heap = find_heap(block, i + 1);
	return heap;
}
