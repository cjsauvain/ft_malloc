#include "ft_malloc.h"

void	create_new_heap(size_t size)
{
	t_heap	*tmp;
	size_t	heap_size;

	tmp = g_heap;
	if (size <= TINY_BLOCK)
		heap_size = TINY_HEAP;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		heap_size = SMALL_HEAP;
	if (g_heap && g_heap->size != heap_size)
		g_heap = g_heap->next;
	g_heap = mmap(NULL, heap_size + sizeof(t_heap), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (g_heap == MAP_FAILED)
		return ;
	g_heap->size = heap_size;
	g_heap->free_block = (t_block *)g_heap + sizeof(t_heap);
	g_heap->free_block->size = heap_size - sizeof(t_heap) + sizeof(t_block);
	if (tmp && g_heap != tmp)
	{
		tmp->next = g_heap;
		g_heap->prev = tmp;
		g_heap = tmp;
	}
}
