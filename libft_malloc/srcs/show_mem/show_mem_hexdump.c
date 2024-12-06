#include "libft_malloc.h"

static void	display_next_block_address(t_heap_group *heap, char *heap_str, t_block *alloc_block)
{
	if (alloc_block->next && ft_strncmp(heap_str, "LARGE", 5))
		ft_printf(BCYN"Next block address:"MAG" %p\n", alloc_block->next);
	else if (heap->next && heap->next->alloc_block \
			&& !ft_strncmp(heap_str, "LARGE", 5))
		ft_printf(BCYN"Next block address:"MAG" %p\n", heap->next->alloc_block);
	else
		ft_printf(BCYN"Next block address:"MAG" None\n", alloc_block->next);
}

static void	loop_alloc_block(t_heap_group *heap, char *heap_str)
{
	t_block	*alloc_block;

	alloc_block = heap->alloc_block;
	while (alloc_block)
	{
		ft_printf(BCYN"Block Address:"MAG" %p\n", alloc_block);
		ft_printf(BCYN"Heap belonging:"MAG" %p (%s)\n", heap, heap_str);
		ft_printf(BCYN"Size:"MAG" %d\n", alloc_block->size);
		display_next_block_address(heap, heap_str, alloc_block);
		ft_printf(BCYN"Content:"MAG"\n");
		display_hexa_format(heap, alloc_block);
		alloc_block = alloc_block->next;
	}
}

static void	display_heap(size_t size, char *heap_str)
{
	t_heap_group	*heap;
	
	heap = select_heap(size);
	if (!heap)
	{
		ft_putchar('\n');
		return ;
	}
	while (heap)
	{
		loop_alloc_block(heap, heap_str);
		heap = heap->next;
	}
}

void	show_mem_hexdump(char *heap_str)
{
	if (!ft_strncmp(heap_str, "ALL", 3))
	{
		display_heap(TINY_BLOCK, "TINY");
		display_heap(SMALL_BLOCK, "SMALL");
		display_heap(SMALL_BLOCK + 1, "LARGE");
	}
	else if (!ft_strncmp(heap_str, "TINY", 4))
		display_heap(TINY_BLOCK, "TINY");
	else if (!ft_strncmp(heap_str, "SMALL", 5))
		display_heap(SMALL_BLOCK, "SMALL");
	else if (!ft_strncmp(heap_str, "LARGE", 5))
		display_heap(SMALL_BLOCK + 1, "LARGE");
}
