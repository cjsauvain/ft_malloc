#include "libft_malloc.h"

static void	update_heap_pos_free_blocks(t_heap_group *new_heap, \
	t_block *free_block, size_t alloc_size)
{
	size_t	offset;

	offset = free_block->aligned_size + sizeof(t_block);
	if ((char *)free_block + offset == (char *)new_heap)
	{
		free_block->size += alloc_size;
		free_block->aligned_size = ALIGN_MEM(free_block->size);
	}
	else
	{
		free_block->next = (t_block *)new_heap;
		free_block->next->prev = free_block;
		free_block->next->next = NULL;
		free_block->next->size = alloc_size - sizeof(t_block);
		free_block->next->aligned_size = ALIGN_MEM(free_block->next->size);
	}
}

void	add_new_heap_free_blocks(t_heap_group *heap_pos, size_t alloc_size)
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
		heap_pos->free_block->aligned_size = ALIGN_MEM(heap_pos->free_block->size);
	}
	heap_pos->aligned_size += ALIGN_MEM(alloc_size);
}
