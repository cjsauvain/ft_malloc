#include "libft_malloc.h"

static t_block	*add_new_alloc_block(t_block *free_block, size_t size, size_t aligned_size)
{
	t_block	*tmp_block = g_heap->alloc_block;

	while (g_heap->alloc_block && g_heap->alloc_block->next)
		g_heap->alloc_block = g_heap->alloc_block->next;
	tmp_block = g_heap->alloc_block;
	//if first allocation
	if (g_heap->alloc_block && !g_heap->alloc_block->next)
		g_heap->alloc_block = g_heap->alloc_block->next;

	g_heap->alloc_block = free_block;
	g_heap->alloc_block->size = size;
	g_heap->alloc_block->aligned_size = aligned_size;
	g_heap->alloc_block->next = NULL;

	if (tmp_block && g_heap->alloc_block != tmp_block)
	{
		tmp_block->next = g_heap->alloc_block;
		g_heap->alloc_block->prev = tmp_block;
	}
	return g_heap->alloc_block;
}

static t_block	*delete_free_block(t_block *free_block, size_t size, size_t aligned_size)
{
	t_block	*tmp = free_block;

	if (!free_block->prev && free_block->next)
	{
		free_block->next->prev = NULL;
		return free_block->next;
	}
	else if (!free_block->prev)
	{
		free_block = (t_block *)((char *)free_block + aligned_size + sizeof(t_block *));
		free_block->size = tmp->size - size - sizeof(t_block *);
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

static void	*first_fit(size_t size, size_t aligned_size)
{
	t_block	*tmp_free = g_heap->free_block;
	t_block	*tmp_block;

	while (tmp_free && tmp_free->size < size)
		tmp_free = tmp_free->next;
	if (!tmp_free) //ne pas retourner null mais faire une nouvelle allocation
		return NULL;
	tmp_block = add_new_alloc_block(tmp_free, size, aligned_size);
	g_heap->free_block = delete_free_block(tmp_free, size, aligned_size);
	return (void *)((char *)tmp_block + sizeof(t_block));
}

void	*get_avail_block(size_t size)
{
	void	*avail_block;
	size_t	aligned_size;

	aligned_size = align_mem(size);
	if (size > SMALL_BLOCK)
	{
		avail_block = mmap(NULL, aligned_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		return avail_block;
	}
	select_heap(size);
	avail_block = first_fit(size, aligned_size);
	return avail_block;
}
