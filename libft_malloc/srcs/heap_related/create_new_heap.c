#include "libft_malloc.h"

t_heap_group	*create_heap(size_t size)
{
	t_heap_group	*new_heap;
	size_t			alloc_size;

	alloc_size = get_alloc_size(size);
	new_heap = mmap(NULL, align_mem(alloc_size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (new_heap == MAP_FAILED)
		return NULL;
	initialize_new_heap(new_heap, alloc_size);
	if (size <= TINY_BLOCK)
		g_heap.tiny_heap = new_heap;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		g_heap.small_heap = new_heap;
	else
		g_heap.large_heap = new_heap;
	return new_heap;
}
