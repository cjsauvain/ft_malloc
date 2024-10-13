#include "libft_malloc.h"

static size_t	display_heap(size_t size, char *size_str)
{
	t_heap_group	*heap;
	t_block			*alloc_block;
	size_t			*beginning_block;
	size_t			*end_block;
	size_t			total_size;
	
	heap = select_heap(size);
	ft_printf("%s : %p\n", size_str, heap);
	if (!heap)
		return 0;
	total_size = 0;
	alloc_block = heap->alloc_block;
	while (alloc_block)
	{
		beginning_block = (size_t *)alloc_block;
		end_block = (size_t *)((char *)alloc_block + sizeof(t_block) + alloc_block->aligned_size);
		ft_printf("%p - %p : %d bytes\n", beginning_block, end_block, alloc_block->size);
		total_size += alloc_block->size;
		alloc_block = alloc_block->next;
	}
	return total_size;
}

void show_alloc_mem(void)
{
	size_t	total_size;

	total_size = display_heap(TINY_BLOCK, "TINY");
	total_size += display_heap(SMALL_BLOCK, "SMALL");
	total_size += display_heap(SMALL_BLOCK + 1, "LARGE");
	ft_printf("Total : %d bytes\n", total_size);
}
