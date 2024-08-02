#include "ft_malloc.h"

int	count_heap(void)
{
	if (!g_heap)
		return 0;
	if (g_heap->prev || g_heap->next)
		return 2;
	return 1;
}

int	check_heap_state(size_t size)
{
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

