#include "../libft/libft.h"
#include "libft_malloc.h"

int	main(void)
{
	char	*p = ft_malloc(5 * sizeof(char));
	p[0] = 'a';
	p[1] = 'b';
	p[2] = 'c';
	p[3] = 'd';
	p[4] = 'e';
	//char	*n = ft_realloc((void *)p, 10 * sizeof(char));

	char	*i = ft_malloc(65 * sizeof(char));
	char	*l = ft_malloc(1000 * sizeof(char));
	(void)i;
	(void)l;

	show_alloc_mem();
	//ft_free(n);
}
