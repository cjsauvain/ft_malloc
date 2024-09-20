#include "libft_malloc.h"

int	count_heap(void)
{
	if (!g_heap)
		return 0;
	if (g_heap->prev || g_heap->next)
		return 2;
	return 1;
}

int	check_heap_left(size_t size)
{
	t_block	*tmp;
	size_t	required_size;

	select_heap(size);
	tmp = g_heap->free_block;
	required_size = 0;
	while (tmp)
	{
		if (required_size >= size)
			return 0;
		if (!tmp-> prev 
			|| (char *)tmp->prev + tmp->prev->aligned_size + sizeof(t_block *) == (char *)tmp)
			required_size += tmp->size;
		else
			required_size = 0;
		tmp = tmp->next;
	}
	if (required_size >= size)
		return 0;
	return 1;
}

int	check_heap_state(size_t size)
{
	if (size > SMALL_BLOCK)
		return 0;
	if (!g_heap)
		return 1;
	if (g_heap->prev)
		g_heap = g_heap->prev;
	else if (count_heap() < 2)
	{
		if (size > TINY_BLOCK && size <= SMALL_BLOCK
			&& g_heap->size == (size_t)TINY_HEAP)
			return 1;
		if (size < TINY_BLOCK && g_heap->size == (size_t)SMALL_HEAP)
			return 1;
	}	
	return 0;
}

void	select_heap(size_t size)
{
	if (size <= TINY_BLOCK && g_heap->size != (size_t)TINY_HEAP)
	{
		if (g_heap->next)
			g_heap = g_heap->next;
		else
			g_heap = g_heap->prev;
	}
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK 
		&& g_heap->size != (size_t)SMALL_HEAP)
	{
		if (g_heap->next)
			g_heap = g_heap->next;
		else
			g_heap = g_heap->prev;
	}
}

