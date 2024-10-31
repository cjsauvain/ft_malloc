#include "libft_malloc_bonus.h"

static void	*first_fit(t_heap_group *heap, size_t size)
{
	t_block	*free_block;
	t_block	*block;

	free_block = heap->free_block;
	while (free_block && free_block->size < size)
		free_block = free_block->next;
	heap->free_block = delete_block(free_block, size, 1);
	block = add_alloc_block(heap, free_block, size);
	return (void *)((char *)block + sizeof(t_block));
}

void	*get_avail_block(t_heap_group *heap, size_t size)
{
	void	*avail_block;

	if (size > SMALL_BLOCK)
	{
		heap->alloc_block = heap->free_block;
		heap->free_block = NULL;
		return (void *)((char *)heap->alloc_block + sizeof(t_block));
	}
	avail_block = first_fit(heap, size);
	return avail_block;
}
