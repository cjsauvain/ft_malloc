#include "libft_malloc.h"

static void	fill_contiguous_free_blocks(t_heap_group *heap_pos, \
	t_block *new_heap_free, size_t alloc_size)
{
	new_heap_free->size = alloc_size + heap_pos->free_block->size;
	new_heap_free->aligned_size = ALIGN_MEM(new_heap_free->size);
	new_heap_free->next = heap_pos->free_block->next;
	heap_pos->free_block->next->prev = new_heap_free;
}

static void	fill_noncontiguous_free_blocks(t_block *new_heap_free, \
	t_block *heap_pos_free, size_t alloc_size)
{
	new_heap_free->size = alloc_size - sizeof(t_block);
	new_heap_free->aligned_size = ALIGN_MEM(new_heap_free->size);
	new_heap_free->next = heap_pos_free;
	if (new_heap_free->next)
		new_heap_free->next->prev = new_heap_free;
}

static void	initialize_new_heap_free_blocks(t_heap_group *new_heap, \
	t_heap_group *heap_pos, size_t alloc_size)
{
	size_t	offset;
	
	offset = ALIGN_MEM(sizeof(t_heap_group));
	if ((char *)heap_pos + offset == (char *)heap_pos->free_block)
		fill_contiguous_free_blocks(heap_pos, new_heap->free_block, alloc_size);
	else
		fill_noncontiguous_free_blocks(new_heap->free_block, \
			heap_pos->free_block, alloc_size);
	new_heap->free_block->prev = NULL;
}

void	add_heap_pos_free_blocks(t_heap_group *heap_pos, \
	t_heap_group *new_heap, size_t alloc_size)
{
	size_t	offset;
	
	if (heap_pos->prev)
		heap_pos->prev->next = new_heap;
	if (heap_pos->next)
		heap_pos->next->prev = new_heap;

	offset = ALIGN_MEM(sizeof(t_heap_group));
	*new_heap = *heap_pos;
	new_heap->aligned_size += ALIGN_MEM(alloc_size);
	new_heap->free_block = (t_block *)((char *)new_heap + offset);
	initialize_new_heap_free_blocks(new_heap, heap_pos, alloc_size);
}
