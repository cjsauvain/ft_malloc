#include "libft_malloc.h"

void	initialize_new_heap(t_heap_group *new_heap, size_t alloc_size)
{
	new_heap->aligned_size = ALIGN_MEM(alloc_size);
	new_heap->alloc_block = NULL;
	new_heap->prev = NULL;
	new_heap->next = NULL;
	new_heap->free_block = (t_block *)((char *)new_heap \
									+ ALIGN_MEM(sizeof(t_heap_group)));
	new_heap->free_block->size = alloc_size - sizeof(t_block) \
									- ALIGN_MEM(sizeof(t_heap_group));
	new_heap->free_block->aligned_size = ALIGN_MEM(new_heap->free_block->size);
	new_heap->free_block->next = NULL;
	new_heap->free_block->prev = NULL;
}
