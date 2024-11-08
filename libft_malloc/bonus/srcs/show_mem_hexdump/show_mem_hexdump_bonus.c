#include "libft_malloc_bonus.h"

static size_t	count_zeros(char *content, size_t increment, size_t size)
{
	size_t	zero_counter;

	zero_counter = 0;
	while (increment < size)
	{
		if (!*(content + increment))
			zero_counter++;
		else
			break ;
		increment++;
	}
	return zero_counter;
}

static void	display_content_in_hexa_format(t_heap_group *heap, t_block *alloc_block)
{
	char	*content;
	size_t	increment;
	size_t	modulo;
	char	buffer[24];
	size_t	zero_counter;
	
	sprintf(buffer, "%08lx   ", (char *)alloc_block - (char *)heap);
	ft_printf("%s", buffer);
	content = (char *)alloc_block + sizeof(t_block);
	increment = 0;
	modulo = 1;
	zero_counter = 0;
	while (increment < alloc_block->size)
	{
		if (!*(content + increment))
			zero_counter = count_zeros(content, increment, alloc_block->size);
		if (!*(content + increment) && zero_counter > 50)
		{
			if (increment >= 12)
				ft_putstr("\n\t   ");
			sprintf(buffer, "00 <%ld times>\n\t  ", zero_counter);
			increment += zero_counter - 1;
			zero_counter = 0;
			modulo = 0;
		}
		else
			sprintf(buffer, "%02x", *(content + increment));
		ft_printf("%s", buffer);
		if (!(modulo % 12) && modulo)
			ft_putstr("\n\t  ");
		if (increment + 1 < alloc_block->size)
			ft_putchar(' ');
		increment++;
		modulo++;
	}
	ft_putstr(BRED"\n\n\t\t****************\n\n"reset);
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
}

void	show_alloc_mem_ex(char *heap_str)
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
