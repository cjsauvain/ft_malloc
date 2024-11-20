#include "libft_malloc_bonus.h"

int	check_heap_state(size_t size)
{
	t_heap_group	*heap;

	heap = select_heap(size);
	if (heap == NULL)
		return 0;
	return 1;
}
