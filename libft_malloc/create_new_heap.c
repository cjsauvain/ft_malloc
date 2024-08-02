#include "ft_malloc.h"

void	*create_new_heap(t_heap *heap, size_t size)
{
	t_heap	*tmp;
	size_t	heap_size;

	tmp = heap;
	if (size <= TINY_BLOCK)
		heap_size = TINY_HEAP;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		heap_size = SMALL_HEAP;
	if (heap && heap->size != heap_size)
		heap = heap->next;
	heap = mmap(NULL, heap_size + sizeof(t_heap), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (heap == MAP_FAILED)
		return MAP_FAILED;
	heap->size = heap_size;
	heap->free_block = (t_block *)heap + sizeof(t_heap);
	heap->free_block->size = heap_size - sizeof(t_heap) + sizeof(t_block);
	if (tmp && heap != tmp)
	{
		tmp->next = heap;
		heap->prev = tmp;
		heap = tmp;
	}
	return heap;
}
