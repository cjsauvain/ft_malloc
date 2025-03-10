#include "libft_malloc.h"

static size_t	loop_alloc_block(t_block *alloc_block)
{
	size_t	*beginning_block;
	size_t	*end_block;
	size_t	size;
	size_t	offset;

	size = 0;
	while (alloc_block)
	{
		offset = alloc_block->aligned_size + sizeof(t_block);
		beginning_block = (size_t *)alloc_block;
		end_block = (size_t *)((char *)alloc_block + offset);
		ft_printf("%p - %p :"YEL" %d bytes\n"RESET, beginning_block, end_block, \
			alloc_block->size);
		size += alloc_block->size;
		alloc_block = alloc_block->next;
	}
	return size;
}

static size_t	display_heap(size_t size, char *size_str)
{
	t_heap_group	*heap;
	size_t			total_size;
	
	heap = select_heap(size);
	if (!heap)
		return 0;
	total_size = 0;
	while (heap)
	{
		ft_printf(URED"%s : %p\n"RESET, size_str, heap);
		total_size += loop_alloc_block(heap->alloc_block);
		heap = heap->next;
	}
	return total_size;
}

void	show_alloc_mem(void)
{
	size_t	total_size;

	total_size = display_heap(TINY_BLOCK, "TINY");
	total_size += display_heap(SMALL_BLOCK, "SMALL");
	total_size += display_heap(SMALL_BLOCK + 1, "LARGE");
	ft_printf(BMAG"Total : %d bytes\n"RESET, total_size);
}
