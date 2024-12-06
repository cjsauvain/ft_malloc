#include "libft_malloc.h"

static t_block	*update_alloc_blocks(t_block *alloc_block, t_block *free_block)
{
	t_block	*tmp;

	tmp = NULL;
	if (alloc_block)
	{
		tmp = alloc_block;
		alloc_block = alloc_block->next;
	}
	alloc_block = free_block;
	alloc_block->next = NULL;
	if (tmp)
	{
		tmp->next = alloc_block;
		alloc_block->prev = tmp;
	}
	return alloc_block;
}

t_block	*add_alloc_block(t_heap_group *heap, t_block *free_block)
{
	t_block	*alloc_block;

	alloc_block = heap->alloc_block;
	while (alloc_block && alloc_block->next)
		alloc_block = alloc_block->next;
	alloc_block = update_alloc_blocks(alloc_block, free_block);
	if (!heap->alloc_block)
		heap->alloc_block = alloc_block;
	return alloc_block;
}
