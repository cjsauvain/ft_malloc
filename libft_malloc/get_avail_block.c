#include "ft_malloc.h"

t_block	*add_new_alloc_block(t_heap *heap, t_block *free_block, size_t size)
{
	t_block	*tmp_block = heap->alloc_block;

	while (heap->alloc_block && heap->alloc_block->next)
		heap->alloc_block = heap->alloc_block->next;
	tmp_block = heap->alloc_block;
	if (heap->alloc_block && !heap->alloc_block->next)
		heap->alloc_block = heap->alloc_block->next;
	heap->alloc_block = (t_block *)free_block + sizeof(t_block);
	heap->alloc_block->size = size + sizeof(t_block); 
	heap->alloc_block->next = NULL;
	if (tmp_block && heap->alloc_block != tmp_block)
	{
		tmp_block->next = heap->alloc_block;
		heap->alloc_block->prev = tmp_block;
	}
	return heap->alloc_block;
}

t_block	*delete_free_block(t_block *free_block, size_t size)
{
	t_block	*tmp = free_block;

	if (!free_block->prev && free_block->next)
	{
		free_block->next->prev = NULL;
		return free_block->next;
	}
	else if (!free_block->prev)
	{
		free_block = (t_block *)((char *)free_block + size);
		free_block->size = tmp->size - size;
		return free_block;
	}
	else if ((char *)free_block->prev + size + sizeof(t_block) == (char *)free_block->next)
	{
		free_block->prev->size += (free_block->next->size + sizeof(t_block));
		free_block->prev->next = free_block->next->next;
	}
	while (free_block && free_block->prev)
		free_block = free_block->prev;
	return free_block;
}

void	*first_fit(t_heap *heap, size_t size)
{
	t_block	*tmp_free = heap->free_block;
	t_block	*tmp_block;

	while (tmp_free && tmp_free->size < size)
		tmp_free = tmp_free->next;
	if (!tmp_free)
		return NULL;
	tmp_block = add_new_alloc_block(heap, tmp_free, size);
	heap->free_block = delete_free_block(tmp_free, size);
	return (void *)tmp_block;
}

void	*get_avail_block(t_heap *heap, size_t size)
{
	t_heap	*tmp;
	void	*avail_block;

	if (size > SMALL_BLOCK)
	{
		avail_block = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		return avail_block;
	}
	tmp = select_heap(heap, size);
	avail_block = first_fit(tmp, size);
	return avail_block;
}
