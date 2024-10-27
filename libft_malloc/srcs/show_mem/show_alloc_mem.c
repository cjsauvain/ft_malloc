#include "libft_malloc.h"

static size_t	display_heap(size_t size, char *size_str)
{
	t_heap_group	*heap;
	t_block			*alloc_block;
	size_t			*beginning_block;
	size_t			*end_block;
	size_t			total_size;
	
	heap = select_heap(size);
	ft_printf(BMAG"%s : %p\n"reset, size_str, heap);
	if (!heap)
	{
		ft_putchar('\n');
		return 0;
	}
	total_size = 0;
	while (heap)
	{
		alloc_block = heap->alloc_block;
		while (alloc_block)
		{
			beginning_block = (size_t *)alloc_block;
			end_block = (size_t *)((char *)alloc_block + sizeof(t_block) + alloc_block->aligned_size);
			ft_printf("%p - %p : %d bytes\n", beginning_block, end_block, alloc_block->size);
			total_size += alloc_block->size;
			alloc_block = alloc_block->next;
		}
		heap = heap->next;
	}
	ft_putchar('\n');
	return total_size;
}

void show_alloc_mem(void)
{
	size_t	total_size;

	total_size = display_heap(TINY_BLOCK, "\nTINY");
	total_size += display_heap(SMALL_BLOCK, "SMALL");
	total_size += display_heap(SMALL_BLOCK + 1, "LARGE");
	ft_printf(URED"Total : %d bytes\n"reset, total_size);
}
