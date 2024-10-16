#include "libft_malloc.h"

static void	merge_blocks(t_heap_group *heap, t_block *block)
{
	if (block->next)
	{
		if (block->prev)
		{
			block->prev->next = block->next;
			block->next->prev = block->prev;
		}
		else
		{
			block->next->prev = NULL;
			heap->alloc_block = block->next;
		}
	}
	else
	{
		if (block->prev)
			block->prev->next = NULL;
	}
	block->size = sizeof(t_block);
	block->aligned_size = align_mem(block->size);
}

static void	munmap_heap(t_heap_group *heap, t_block *block, void *ptr)
{
	t_heap_group	*prev_heap;
	t_heap_group	*next_heap;
	size_t			alloc_size;

	alloc_size = block->size + sizeof(t_heap_group) + sizeof(t_block);
	ptr = (void *)((char *)ptr - sizeof(t_block) - sizeof(t_heap_group));
	prev_heap = heap->prev;
	next_heap = heap->next;
	status = munmap(ptr, alloc_size);
	if (!status)
		merge_heaps(prev_heap, next_heap, alloc_size);
}

static void	free_block(t_heap_group *heap, t_block *block, void *ptr)
{
	t_block	*alloc_block;

	alloc_block = heap->alloc_block;
	
}

void	ft_free(void *ptr)
{
	t_heap_group	*heap;
	t_block			*block;
	int				status;
	size_t			alloc_size;

	block = (t_block *)((char *)ptr - sizeof(t_block));
	heap = find_heap(block->heap_index, 0);
	block = find_ptr_block(heap, ptr);
	if (block->size > SMALL_BLOCK)
		munmap_heap(heap, block, ptr);
	else
		free_block(heap, block, ptr);
}
