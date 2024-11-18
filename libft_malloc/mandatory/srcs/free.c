#include "libft_malloc.h"

static void	update_heaps(t_heap_group *prev_heap, t_heap_group *next_heap)
{
	if (!prev_heap && !next_heap)
		g_heap.large_heap = NULL;
	else if (!prev_heap)
	{
		next_heap->prev = NULL;
		g_heap.large_heap = next_heap;
	}
	else if (!next_heap)
		prev_heap->next = NULL;
	else
	{
		prev_heap->next = next_heap;
		next_heap->prev = prev_heap;
	}
}

static void	munmap_heap(t_heap_group *heap, t_block *block)
{
	t_heap_group	*prev_heap;
	t_heap_group	*next_heap;
	void			*ptr;
	size_t			alloc_size;
	int				status;

	alloc_size = block->size + sizeof(t_heap_group) + sizeof(t_block);
	ptr = (void *)((char *)block - sizeof(t_heap_group));
	prev_heap = heap->prev;
	next_heap = heap->next;
	status = munmap(ptr, ALIGN_MEM(alloc_size));
	if (!status)
		update_heaps(prev_heap, next_heap);
}

static void	free_block(t_heap_group *heap, t_block *block)
{
	heap->alloc_block = delete_block(block, block->size, 0);
	add_free_block(heap, block);
}

void	ft_free(void *ptr)
{
	t_heap_group	*heap;
	t_block			*block;

	block = (t_block *)((char *)ptr - sizeof(t_block));
	heap = find_heap(block, 0);
	if (!heap)
		return ;
	if (block->size > SMALL_BLOCK)
		munmap_heap(heap, block);
	else
		free_block(heap, block);
}
