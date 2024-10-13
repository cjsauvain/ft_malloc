#include "libft_malloc.h"

static t_block	*add_new_alloc_block(t_heap_group *heap, t_block *free_block, size_t size)
{
	t_block	*alloc_block;
	t_block	*tmp;
	size_t	aligned_size;

	alloc_block = heap->alloc_block;
	tmp = NULL;
	aligned_size = align_mem(size);
	while (alloc_block && alloc_block->next)
		alloc_block = alloc_block->next;
	if (alloc_block)
	{
		tmp = alloc_block;
		alloc_block = alloc_block->next;
	}
	alloc_block = free_block;
	alloc_block->size = size;
	alloc_block->aligned_size = aligned_size;
	alloc_block->next = NULL;
	if (tmp)
	{
		tmp->next = alloc_block;
		alloc_block->prev = tmp;
	}
	if (!heap->alloc_block)
		heap->alloc_block = alloc_block;
	return heap->alloc_block;
}

static t_block	*delete_free_block(t_block *free_block, size_t size) //raccourcir la fonction
{
	t_block	*tmp;
	size_t	aligned_size;

	tmp = free_block;
	aligned_size = align_mem(size);
	if (!free_block->prev && free_block->next)
	{
		free_block->next->prev = NULL;
		return free_block->next;
	}
	else if (!free_block->prev)
	{
		free_block = (t_block *)((char *)free_block + aligned_size + sizeof(t_block));
		free_block->size = tmp->size - size - sizeof(t_block);
		free_block->aligned_size = tmp->aligned_size - aligned_size;
		free_block->next = NULL;
		free_block->prev = NULL;
		return free_block;
	}
	else if ((char *)free_block->prev + free_block->prev->aligned_size + sizeof(t_block) == (char *)free_block->next)
	{
		free_block->prev->size += (free_block->next->size + sizeof(t_block));
		free_block->prev->aligned_size += (free_block->next->aligned_size + sizeof(t_block));
		free_block->prev->next = free_block->next->next;
	}
	else
		free_block->prev->next = free_block->next;
	while (free_block && free_block->prev)
		free_block = free_block->prev;
	return free_block;
}

static void	*first_fit(t_heap_group *heap, size_t size)
{
	t_block	*free_block;
	t_block	*block;

	free_block = heap->free_block;
	while (free_block && free_block->size < size)
		free_block = free_block->next;
	if (!free_block) //ne pas retourner null mais faire une nouvelle allocation
		return NULL;
	heap->free_block = delete_free_block(free_block, size);
	block = add_new_alloc_block(heap, free_block, size);
	return (void *)((char *)block + sizeof(t_block));
}

void	*get_avail_block(t_heap_group *heap, size_t size)
{
	void	*avail_block;

	if (!heap->free_block)
	{

	}
	avail_block = first_fit(heap, size);
	return avail_block;
}
