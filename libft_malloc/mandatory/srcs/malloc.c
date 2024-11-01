#include "libft_malloc.h"

t_heap	g_heap = {};

void	*ft_malloc(size_t size)
{
	t_heap_group	*heap;
	void			*block;
	int				heap_state;

	heap = NULL;
	if (!size)
		return NULL;
	heap_state = check_heap_state(size);
	if (!heap_state)
		heap = create_heap(size);
	else
	{
		heap = check_heap_left(size);
		if (!heap)
			heap = add_heap(size);
	}
	if (!heap)
		return NULL;
	block = get_avail_block(heap, size);
	return block;
}
