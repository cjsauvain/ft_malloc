#include "libft_malloc_bonus.h"

size_t	get_heap_group(size_t size)
{
	if (size <= TINY_BLOCK)
		return TINY_HEAP;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		return SMALL_HEAP;
	return (size + ALIGN_MEM(sizeof(t_heap_group)) + sizeof(t_block));
}
