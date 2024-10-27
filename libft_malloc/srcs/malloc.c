#include "libft_malloc.h"

t_heap	g_heap = {};

void	*ft_malloc(size_t size)
{
	t_heap_group	*heap = NULL;
	void			*block;
	int				heap_state;

	if (!size)
		return NULL;
	heap_state = check_heap_state(size);
	if (!heap_state)
		heap = allocate_heap(size, 0);
	else
	{
		heap = check_heap_left(size);
		if (!heap)
			heap = allocate_heap(size, 1);
	}
	if (!heap)
		return NULL;
	block = get_avail_block(heap, size);
	return block;
}
