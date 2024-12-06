#include "libft_malloc.h"

static size_t	count_zeros(char *content, size_t increment, \
					size_t size)
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

static void	print_zeros(char *buffer, size_t *increment, \
				size_t *zero_counter, size_t *modulo)
{
	if (*increment >= 12)
		ft_putstr("\n\t   ");
	sprintf(buffer, "00 <%ld times>\n\t  ", *zero_counter);
	*increment += *zero_counter - 1;
	*zero_counter = 0;
	*modulo = 0;
}

static void	print_white_spaces(size_t alloc_block_size, \
				size_t increment, size_t modulo)
{
	if (!(modulo % 12) && modulo)
		ft_putstr("\n\t  ");
	if (increment + 1 < alloc_block_size)
		ft_putchar(' ');
}

void	display_hexa_format(t_heap_group *heap, t_block *alloc_block)
{
	char	*content;
	char	buffer[24];
	size_t	increment = 0;
	size_t	modulo = 1;
	size_t	zero_counter = 0;
	
	sprintf(buffer, "%08lx   ", (char *)alloc_block - (char *)heap);
	ft_printf("%s", buffer);

	content = (char *)alloc_block + sizeof(t_block);
	while (increment < alloc_block->size)
	{
		if (!*(content + increment))
			zero_counter = count_zeros(content, increment, alloc_block->size);
		if (!*(content + increment) && zero_counter >= 50)
			print_zeros(buffer, &increment, &zero_counter, &modulo);
		else
			sprintf(buffer, "%02x", *(content + increment));
		ft_printf("%s", buffer);
		print_white_spaces(alloc_block->size, increment, modulo);
		increment++;
		modulo++;
	}
	ft_putstr(BRED"\n\n\t\t****************\n\n"RESET);
}
