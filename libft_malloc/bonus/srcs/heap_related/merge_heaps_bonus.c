#include "libft_malloc_bonus.h"

static void	update_heap_pos_free_blocks(t_heap_group *new_heap, \
	t_block *free_block, size_t alloc_size)
{
	size_t	offset;

	offset = free_block->aligned_size + sizeof(t_block);
	if ((char *)free_block + offset == (char *)new_heap)
	{
		free_block->size += alloc_size;
		free_block->aligned_size = align_mem(free_block->size);
	}
	else
	{
		free_block->next = (t_block *)new_heap;
		free_block->next->prev = free_block;
		free_block->next->next = NULL;
		free_block->next->size = alloc_size - sizeof(t_block);
		free_block->next->aligned_size = align_mem(free_block->next->size);
	}
}

static void	add_new_heap_free_blocks(t_heap_group *heap_pos, size_t alloc_size)
{
	t_block	*tmp_free;

	tmp_free = heap_pos->free_block;
	while (tmp_free && tmp_free->next)
		tmp_free = tmp_free->next;
	if (tmp_free)
		update_heap_pos_free_blocks(heap_pos, tmp_free, alloc_size);
	if (!tmp_free)
	{
		heap_pos->free_block->size = alloc_size - sizeof(t_block);
		heap_pos->free_block->aligned_size = align_mem(heap_pos->free_block->size);
	}
	heap_pos->aligned_size += align_mem(alloc_size);
}

static void	fill_contiguous_free_blocks(t_heap_group *heap_pos, \
	t_block *new_heap_free, size_t alloc_size)
{
	new_heap_free->size = alloc_size + heap_pos->free_block->size;
	new_heap_free->aligned_size = align_mem(new_heap_free->size);
	new_heap_free->next = heap_pos->free_block->next;
	heap_pos->free_block->next->prev = new_heap_free;
}

static void	fill_noncontiguous_free_blocks(t_block *new_heap_free, \
	t_block *heap_pos_free, size_t alloc_size)
{
	new_heap_free->size = alloc_size - sizeof(t_block);
	new_heap_free->aligned_size = align_mem(new_heap_free->size);
	new_heap_free->next = heap_pos_free;
	new_heap_free->next->prev = new_heap_free;
}

static void	initialize_new_heap_free_blocks(t_heap_group *new_heap, \
	t_heap_group *heap_pos, size_t alloc_size)
{
	if ((char *)heap_pos + sizeof(t_heap_group) == (char *)heap_pos->free_block)
		fill_contiguous_free_blocks(heap_pos, new_heap->free_block, alloc_size);
	else
		fill_noncontiguous_free_blocks(new_heap->free_block, \
			heap_pos->free_block, alloc_size);
	new_heap->free_block->prev = NULL;
}

static void	add_heap_pos_free_blocks(t_heap_group *heap_pos, \
	t_heap_group *new_heap, size_t alloc_size)
{
	if (heap_pos->prev)
		heap_pos->prev->next = new_heap;
	if (heap_pos->next)
		heap_pos->next->prev = new_heap;

	*new_heap = *heap_pos;
	new_heap->aligned_size += align_mem(alloc_size);
	new_heap->free_block = (t_block *)((char *)new_heap + sizeof(t_heap_group));
	initialize_new_heap_free_blocks(new_heap, heap_pos, alloc_size);
}

t_heap_group	*merge_heaps(t_heap_group *heap_pos, t_heap_group *new_heap, \
	size_t alloc_size)
{
	if (heap_pos < new_heap)
	{
		add_new_heap_free_blocks(heap_pos, alloc_size);
		return heap_pos;
	}
	add_heap_pos_free_blocks(heap_pos, new_heap, alloc_size);
	return new_heap;
}
