#include "libft_malloc_bonus.h"

static size_t	get_required_size(t_block *heap_free, size_t size)
{
	size_t	required_size;
	size_t	offset;

	required_size = 0;
	offset = 0;
	while (heap_free && required_size < size)
	{
		if (heap_free->prev)
			offset = heap_free->prev->aligned_size + sizeof(t_block);
		if (!heap_free->prev)
			required_size += heap_free->size;
		else if ((char *)heap_free->prev + offset == (char *)heap_free)
			required_size += heap_free->size;
		else
			required_size = 0;
		heap_free = heap_free->next;
	}
	return required_size;
}

t_heap_group	*check_heap_left(size_t size)
{
	t_heap_group	*heap;
	size_t			required_size;

	if (size > SMALL_BLOCK)
		return NULL;
	heap = select_heap(size);
	required_size = 0;
	while (heap)
	{
		required_size = get_required_size(heap->free_block, size);
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

size_t	get_heap_group(size_t size)
{
	if (size <= TINY_BLOCK)
		return TINY_HEAP;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		return SMALL_HEAP;
	return (size + sizeof(t_heap_group) + sizeof(t_block));
}
