#include "libft_malloc.h"

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
		//check if block exist in a function
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

void	initialize_new_heap(t_heap_group *new_heap, size_t alloc_size)
{
	new_heap->aligned_size = align_mem(alloc_size);
	new_heap->alloc_block = NULL;
	new_heap->prev = NULL;
	new_heap->next = NULL;
	new_heap->free_block = (t_block *)((char *)new_heap + sizeof(t_heap_group));
	new_heap->free_block->size = alloc_size - sizeof(t_block) - sizeof(t_heap_group);
	new_heap->free_block->aligned_size = align_mem(new_heap->free_block->size);
	new_heap->free_block->next = NULL;
	new_heap->free_block->prev = NULL;
}

size_t	get_alloc_size(size_t size)
{
	if (size <= TINY_BLOCK)
		return TINY_HEAP;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		return SMALL_HEAP;
	return (size + sizeof(t_heap_group) + sizeof(t_block));
}
