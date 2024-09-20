#include "libft_malloc.h"

static void	create_heap(size_t heap_size, size_t aligned_size)
{
	t_heap	*tmp;

	tmp = g_heap;
	if (g_heap && g_heap->size != heap_size)
		g_heap = g_heap->next;
	g_heap->free_block = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (g_heap->free_block == MAP_FAILED)
		return ;
	g_heap->size = heap_size;
	g_heap->aligned_size = aligned_size;
	g_heap->free_block->size = heap_size - sizeof(t_block);
	g_heap->free_block->aligned_size = aligned_size - sizeof(t_block);
	g_heap->free_block->next = NULL;
	g_heap->free_block->prev = NULL;
	g_heap->alloc_block = NULL;
	if (tmp && g_heap != tmp)
	{
		tmp->next = g_heap;
		g_heap->prev = tmp;
		g_heap = tmp;
	}
}

static void	add_heap(size_t heap_size, size_t aligned_size)
{
	t_block	*tmp;

	if (g_heap->size != heap_size && g_heap->next)
		g_heap = g_heap->next;
	tmp = g_heap->free_block;

	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->next = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		if (tmp->next == MAP_FAILED)
			return ;
		g_heap->size += heap_size;
		g_heap->aligned_size += aligned_size;
		tmp->next->size = heap_size - sizeof(t_block *);
		tmp->next->aligned_size = aligned_size - sizeof(t_block *);
		tmp->next->prev = tmp;
		tmp->next->prev = NULL;
	}

	if (g_heap->prev)
		g_heap = g_heap->prev;
}

void	allocate_heap(size_t size, int mode)
{
	size_t	heap_size;
	size_t	aligned_size;

	if (size <= TINY_BLOCK)
		heap_size = TINY_HEAP;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		heap_size = SMALL_BLOCK;
	aligned_size = align_mem(heap_size);
	if (!mode)
		add_heap(heap_size, aligned_size);
	else
		create_heap(heap_size, aligned_size);
}
