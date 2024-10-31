#include "libft_malloc_bonus.h"

t_heap_group	*allocate_heap(size_t size, int mode)
{
	t_heap_group	*heap;

	if (mode)
		heap = add_heap(size);
	else
		heap = create_heap(size);
	return heap;
}
