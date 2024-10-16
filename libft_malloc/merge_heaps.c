#include "libft_malloc.h"

static void	add_new_heap_free_blocks(t_heap_group *heap_pos, t_heap_group *new_heap, size_t alloc_size)
{
	t_block	*tmp_free;
	size_t	aligned_alloc_size;

	tmp_free = heap_pos->free_block;
	while (tmp_free && tmp_free->next)
		tmp_free = tmp_free->next;
	if (tmp_free)
	{
		aligned_alloc_size = align_mem(alloc_size);
		tmp_free->next = (t_block *)new_heap;
		tmp_free->next->prev = tmp_free;
		tmp_free->next->next = NULL;
		tmp_free->next->size = alloc_size - sizeof(t_block);
		tmp_free->next->aligned_size = aligned_alloc_size - sizeof(t_block);
		tmp_free->next->heap_index = heap_pos->index;
		heap_pos->aligned_size += aligned_alloc_size;
	}
}

static void	add_heap_pos_free_blocks(t_heap_group *heap_pos, t_heap_group *new_heap, size_t alloc_size)
{
	size_t	aligned_alloc_size;

	if (heap_pos->prev)
		heap_pos->prev->next = new_heap;
	if (heap_pos->next)
		heap_pos->next->prev = new_heap;

	aligned_alloc_size = align_mem(alloc_size);
	*new_heap = *heap_pos;
	new_heap->aligned_size += aligned_alloc_size;
	new_heap->free_block = (t_block *)((char *)new_heap + sizeof(t_heap_group));
	new_heap->free_block->heap_index = heap_pos->index;
	new_heap->free_block->size = alloc_size - sizeof(t_heap_group) - sizeof(t_block);
	new_heap->free_block->aligned_size = aligned_alloc_size - sizeof(t_heap_group) - sizeof(t_block);
	new_heap->free_block->next = heap_pos->free_block;
	new_heap->free_block->prev = NULL;
	heap_pos->free_block->prev = new_heap->free_block;
}

t_heap_group	*merge_heaps(t_heap_group *heap_pos, t_heap_group *new_heap, size_t alloc_size)
{
	if (heap_pos < new_heap)
	{
		add_new_heap_free_blocks(heap_pos, new_heap, alloc_size);
		return heap_pos;
	}
	add_heap_pos_free_blocks(heap_pos, new_heap, alloc_size);
	return new_heap;
}
