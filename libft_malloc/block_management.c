#include "libft_malloc.h"

t_block	*add_block(t_heap_group *heap, t_block *free_block, size_t size)
{//raccourcir la fonction si possible
	t_block	*alloc_block;
	t_block	*tmp;
	size_t	aligned_size;

	alloc_block = heap->alloc_block;
	tmp = NULL;
	aligned_size = align_mem(size);
	while (alloc_block && alloc_block->next)
		alloc_block = alloc_block->next;
	if (alloc_block)
	{
		tmp = alloc_block;
		alloc_block = alloc_block->next;
	}
	alloc_block = free_block;
	alloc_block->size = size;
	alloc_block->aligned_size = aligned_size;
	alloc_block->next = NULL;
	if (tmp)
	{
		tmp->next = alloc_block;
		alloc_block->prev = tmp;
	}
	if (!heap->alloc_block)
		heap->alloc_block = alloc_block;
	return heap->alloc_block;
}

t_block	*delete_block(t_block *block, size_t size) //raccourcir la fonction
{
	t_block	*tmp;
	size_t	aligned_size;

	tmp = block;
	aligned_size = align_mem(size);
	if (!block->prev && block->next)
	{
		block->next->prev = NULL;
		return block->next;
	}
	else if (!block->prev)
	{
		if (block->aligned_size == aligned_size)
			//a faire;
		block = (t_block *)((char *)block + aligned_size + sizeof(t_block));
		block->size = tmp->size - size - sizeof(t_block);
		block->aligned_size = tmp->aligned_size - aligned_size;
		block->next = NULL;
		block->prev = NULL;
		return block;
	}
	else if ((char *)block->prev + block->prev->aligned_size + sizeof(t_block) == (char *)block->next)
	{
		block->prev->size += (block->next->size + sizeof(t_block));
		block->prev->aligned_size += (block->next->aligned_size + sizeof(t_block));
		block->prev->next = block->next->next;
	}
	else
		block->prev->next = block->next;
	while (block && block->prev)
		block = block->prev;
	return block;
}
