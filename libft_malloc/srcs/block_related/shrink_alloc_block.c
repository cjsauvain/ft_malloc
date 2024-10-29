#include "libft_malloc.h"


t_block	*shrink_alloc_block(t_heap_group *heap, t_block *ptr_block, size_t realloc_size)
{
	t_block	*freed_block;
	size_t	aligned_realloc_size;

	aligned_realloc_size = align_mem(realloc_size);
	freed_block = (t_block *)((char *)ptr_block + sizeof(t_block) + aligned_realloc_size);
	freed_block->size = ptr_block->size - realloc_size - sizeof(t_block);
	freed_block->aligned_size = align_mem(freed_block->size);
	add_free_block(heap, freed_block);

	ptr_block->size = realloc_size;
	ptr_block->aligned_size = aligned_realloc_size;

	return ptr_block;
}
