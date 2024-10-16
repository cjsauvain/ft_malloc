#include "../libft/libft.h"
#include "libft_malloc.h"

int	main(void)
{
	char	*a = ft_malloc(5 * sizeof(char));
	char	*b = ft_malloc(30 * sizeof(char));
	char	*c = ft_malloc(22 * sizeof(char));
	char	*d = ft_malloc(57 * sizeof(char));
	//char	*n = ft_realloc((void *)p, 10 * sizeof(char));

	char	*e = ft_malloc(65 * sizeof(char));
	char	*f = ft_malloc(122 * sizeof(char));
	char	*g = ft_malloc(265 * sizeof(char));
	char	*h = ft_malloc(444 * sizeof(char));
	char	*i = ft_malloc(511 * sizeof(char));

	char	*j = ft_malloc(1000 * sizeof(char));
	char	*k = ft_malloc(16540 * sizeof(char));
	char	*l = ft_malloc(15166 * sizeof(char));
	char	*m = ft_malloc(15665 * sizeof(char));
	char	*n = ft_malloc(6667 * sizeof(char));
	(void)a;
	(void)b;
	(void)c;
	(void)d;
	(void)e;
	(void)f;
	(void)g;
	(void)h;
	(void)i;
	(void)j;
	(void)k;
	(void)l;
	(void)m;


	show_alloc_mem();
	ft_free(n);
}
