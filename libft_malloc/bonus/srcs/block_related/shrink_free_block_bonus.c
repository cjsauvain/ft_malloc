#include "libft_malloc_bonus.h"

static void	put_realloc_block_before_alloc_block(t_block *realloc_block, \
	t_block *alloc_block)
{
	if (!alloc_block->prev)
	{
		alloc_block->prev = realloc_block;
		realloc_block->next = alloc_block;
		realloc_block->prev = NULL;
	}
	else
	{
		realloc_block->next = alloc_block;
		realloc_block->prev = alloc_block->prev;
		alloc_block->prev->next = realloc_block;
		alloc_block->prev = realloc_block;
	}
}

static void	put_realloc_block_after_alloc_block(t_block *realloc_block, \
	t_block *alloc_block)
{
	if (!alloc_block->next)
	{
		alloc_block->next = realloc_block;
		realloc_block->prev = alloc_block;
		realloc_block->next = NULL;
	}
	else
	{
		realloc_block->next = alloc_block->next;
		realloc_block->prev = alloc_block;
		alloc_block->next->prev = realloc_block;
		alloc_block->next = realloc_block;
	}
}

static void	add_realloc_block(t_block *alloc_block, t_block *realloc_block)
{
	while (alloc_block && alloc_block->next && realloc_block > alloc_block)
		alloc_block = alloc_block->next;

	if (realloc_block < alloc_block)
		put_realloc_block_before_alloc_block(realloc_block, alloc_block);
	else
		put_realloc_block_after_alloc_block(realloc_block, alloc_block);
}

static void	remove_ptr_block(t_heap_group *heap, t_block *ptr_block)
{
	if (!ptr_block->prev)
	{
		heap->alloc_block = ptr_block->next;
		if (ptr_block->next)
			ptr_block->next->prev = NULL;
	}
	else if (!ptr_block->next)
	{
		if (ptr_block->prev)
			ptr_block->prev->next = NULL;
	}
	else
	{
		ptr_block->prev->next = ptr_block->next;
		ptr_block->next->prev = ptr_block->prev;
	}
}

t_block	*shrink_free_block(t_heap_group *heap, t_block *ptr_block, \
	t_block *realloc_block, size_t realloc_size)
{
	t_block	*tmp_block;
	size_t	aligned_realloc_size;
	size_t	offset;

	aligned_realloc_size = ALIGN_MEM(realloc_size);
	offset = aligned_realloc_size + sizeof(t_block);
	tmp_block = (t_block *)((char *)realloc_block + offset);
	tmp_block->size = realloc_block->size - realloc_size - sizeof(t_block);
	tmp_block->aligned_size = ALIGN_MEM(tmp_block->size);
	heap->free_block = tmp_block;
	realloc_block->size = realloc_size;
	realloc_block->aligned_size = aligned_realloc_size;

	add_realloc_block(heap->alloc_block, realloc_block);
	remove_ptr_block(heap, ptr_block);

	return realloc_block;
}
