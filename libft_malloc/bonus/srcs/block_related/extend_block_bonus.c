#include "libft_malloc_bonus.h"

static void	merge_blocks(t_block *block, size_t required_size)
{
	if (block->size == required_size)
		return ;
	required_size -= block->size;
	while (block && required_size)
	{
		block->prev->size += block->size + sizeof(t_block);
		block->prev->aligned_size = ALIGN_MEM(block->prev->size);
		block->prev->next = block->next;
		block = block->prev;
		required_size -= block->size;
	}
}

static size_t	get_required_size(t_block *tmp, size_t realloc_size)
{
	size_t	required_size;
	size_t	offset;

	required_size = 0;
	offset = 0;
	while (tmp)
	{
		if (tmp->prev)
			offset = tmp->prev->aligned_size + sizeof(t_block);
		if (!tmp->prev)
			required_size += tmp->size;
		else if ((char *)tmp->prev + offset == (char *)tmp)
			required_size += tmp->size;
		else
			required_size = 0;
		if (required_size >= realloc_size)
			return required_size;
		tmp = tmp->next;
	}
	return 0;
}

void	*extend_block(t_heap_group *heap, t_block *ptr_block, \
	size_t realloc_size)
{
	t_block	*free_block;
	void	*new_ptr;
	size_t	required_size;

	free_block = heap->free_block;
	required_size = get_required_size(free_block, realloc_size);
	if (required_size >= realloc_size)
	{
		merge_blocks(free_block, required_size);
		new_ptr = shrink_free_block(heap, ptr_block, free_block, realloc_size);
	}
	else
	{
		new_ptr = malloc(realloc_size);
		if (!new_ptr)
			return NULL;
		if (ptr_block->prev)
			ptr_block->prev->next = ptr_block->next;
		if (ptr_block->next)
			ptr_block->next->prev = ptr_block->prev;
	}
	add_free_block(heap, ptr_block);
	return new_ptr;
}
