#include "libft_malloc_bonus.h"

static void	display_content_in_hexa_format(t_heap_group *heap, t_block *alloc_block)
{
	char	*content;
	size_t	offset_heap;
	size_t	increment;
	size_t	modulo;
	char	buffer[12];
	
	offset_heap = (char *)alloc_block - (char *)heap;
	sprintf(buffer, "%08lx   ", offset_heap);
	ft_printf("%s", buffer);
	content = (char *)alloc_block + sizeof(t_block);
	increment = 0;
	modulo = 1;
	while (increment < alloc_block->size)
	{
		sprintf(buffer, "%02x", *(content + increment));
		ft_printf("%s", buffer);
		if (!(modulo % 12) && modulo)
			ft_putstr("\n          ");
		if (increment + 1 < alloc_block->size)
			ft_putchar(' ');
		increment++;
		modulo++;
	}
	ft_putstr("\n\n\n");
}

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
		display_content_in_hexa_format(heap, alloc_block);
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
	ft_putstr(YEL"--------------------------------------------------\n\n"reset);
}

void	show_alloc_mem(char *heap_str)
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
