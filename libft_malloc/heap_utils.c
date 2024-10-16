#include "libft_malloc.h"

t_heap_group	*find_heap(int heap_index, int i)
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
		if (heap->index == heap_index)
			break ;
		heap = heap->next;
	}
	if (i == 2 && !heap)
		return NULL;
	else if (!heap)
		heap = find_heap(heap_index, i + 1);
	return heap;
}

t_heap_group	*check_heap_left(size_t size)
{
	t_block			*tmp;
	t_heap_group	*heap;
	size_t			required_size;

	if (size > SMALL_BLOCK)
		return NULL;
	heap = select_heap(size);
	while (heap)
	{
		required_size = 0;
		tmp = heap->free_block;
		while (tmp && required_size <= size)
		{
			if (!tmp->prev 
				|| (char *)tmp->prev + tmp->prev->aligned_size + sizeof(t_block) == (char *)tmp)
				required_size += tmp->size;
			else
				required_size = 0;
			tmp = tmp->next;
		}
		if (required_size >= size)
			return heap;
		heap = heap->next;
	}
	return NULL;
}

int	check_heap_state(size_t size)
{
	t_heap_group	*heap;

	heap = select_heap(size);
	if (heap == NULL)
		return 0;
	return 1;
}

t_heap_group	*select_heap(size_t size)
{
	if (size <= TINY_BLOCK)
		return g_heap.tiny_heap;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		return g_heap.small_heap;
	return g_heap.large_heap;
}
