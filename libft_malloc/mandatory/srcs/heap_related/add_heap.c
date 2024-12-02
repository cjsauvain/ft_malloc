#include "libft_malloc.h"

static void	add_new_heap(t_heap_group *new_heap, \
	size_t alloc_size, size_t size)
{
	t_heap_group	*heaps;

	heaps = select_heap(size);
	while (heaps && heaps->next)
		heaps = heaps->next;
	if (heaps)
	{
		initialize_new_heap(new_heap, alloc_size);
		new_heap->prev = heaps;
		heaps->next = new_heap;
	}
}

static t_heap_group	*check_if_heap_contiguous(t_heap_group *new_heap, \
	size_t alloc_size, size_t size)
{
	t_heap_group	*heaps;
	size_t			offset;

	heaps = select_heap(size);
	while (heaps)
	{
		offset = heaps->aligned_size + ALIGN_MEM(sizeof(t_heap_group));
		if ((char *)new_heap + alloc_size == (char *)heaps)
			return heaps;
		else if ((char *)heaps + offset == (char *)new_heap)
			return heaps;
		heaps = heaps->next;
	}
	return NULL;
}

t_heap_group	*add_heap(size_t size)
{
	t_heap_group	*new_heap;
	t_heap_group	*heap_pos;
	size_t			alloc_size;

	alloc_size = get_heap_group(size);
	new_heap = mmap(NULL, ALIGN_MEM(alloc_size), \
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (new_heap == MAP_FAILED)
		return NULL;
	if (size <= SMALL_BLOCK)
	{
		heap_pos = check_if_heap_contiguous(new_heap, alloc_size, size);
		if (heap_pos)
		{
			new_heap = merge_heaps(heap_pos, new_heap, alloc_size);
			return new_heap;
		}
	}
	add_new_heap(new_heap, alloc_size, size);
	return new_heap;
}
