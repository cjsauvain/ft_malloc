#include "libft_malloc.h"

t_heap	*g_heap = NULL;

void	*ft_malloc(size_t size)
{
	void	*alloc_block;

	if (!size)
		return NULL;
	else if (check_heap_state(size))
		allocate_new_heap(size, 0);
	else if (check_heap_left(size))
		allocate_heap(size, 1);
	else if (g_heap == MAP_FAILED)
		return NULL;
	alloc_block = get_avail_block(size);
	if (g_heap && g_heap->prev)
		g_heap = g_heap->prev;
	return alloc_block;
}
