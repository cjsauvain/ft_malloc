#include "libft_malloc.h"

t_block	*find_ptr_block(t_heap_group *heap, void *ptr)
{
	t_block	*block;

	while (heap)
	{
		block = heap->alloc_block;
		while (block)
		{
			if ((char *)block + sizeof(t_block) == ptr)
				return block;
		}
		heap = heap->next;
	}
	return NULL;
}
