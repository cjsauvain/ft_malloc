#include "libft_malloc/bonus/include/libft_malloc_bonus.h"

int	main(void)
{
	char	*a = ft_malloc(5 * sizeof(char));
	char	*b = ft_malloc(30 * sizeof(char));
	char	*c = ft_malloc(22 * sizeof(char));
	char	*d = ft_malloc(57 * sizeof(char));

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


	char	*reall = ft_realloc(n, 54 * sizeof(char));

	ft_strlcpy(a, "abcd", 5);
	ft_strlcpy(b, "Bonjour", 8);
	ft_strlcpy(c, "Je m'appelle", 13);
	ft_strlcpy(d, "Jordan", 7);
	ft_strlcpy(&d[20], "aaaa", 5);
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
	(void)reall;


	show_alloc_mem_ex("TINY");
	ft_free(a);
	ft_free(b);
	ft_free(c);
	ft_free(d);
	ft_free(d);
	ft_free(e);
	ft_free(f);
	ft_free(h);
	ft_free(j);
	ft_free(k);
	ft_free(l);
	ft_free(m);
	ft_free(n);
	ft_free(reall);
}
