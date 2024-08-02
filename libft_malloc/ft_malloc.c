#include "ft_malloc.h"

t_heap	*g_heap = NULL;

void	*ft_malloc(size_t size)
{
	void	*alloc_block;
	size_t	aligned_size;

	aligned_size = align4(size);
	if (check_heap_state(aligned_size))
		create_new_heap(aligned_size);
	if (g_heap == MAP_FAILED)
		return NULL;
	alloc_block = get_avail_block(aligned_size);
	return alloc_block;
}
