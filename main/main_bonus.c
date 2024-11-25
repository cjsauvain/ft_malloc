#include "../libft_malloc/bonus/include/libft_malloc_bonus.h"

int	main(void)
{
	char	*a = malloc(5 * sizeof(char));
	char	*b = malloc(30 * sizeof(char));
	char	*c = malloc(22 * sizeof(char));
	char	*d = malloc(57 * sizeof(char));

	char	*e = malloc(65 * sizeof(char));
	char	*f = malloc(122 * sizeof(char));
	char	*g = malloc(265 * sizeof(char));
	char	*h = malloc(444 * sizeof(char));
	char	*i = malloc(511 * sizeof(char));

	char	*j = malloc(1000 * sizeof(char));
	char	*k = malloc(16540 * sizeof(char));
	char	*l = malloc(15166 * sizeof(char));
	char	*m = malloc(15665 * sizeof(char));
	char	*n = malloc(6667 * sizeof(char));


	char	*reall = realloc(n, 54 * sizeof(char));

	ft_strlcpy(a, "abcd", 5);
	ft_strlcpy(b, "Bonjour", 8);
	ft_strlcpy(c, "Je m'appelle", 13);
	ft_strlcpy(d, "Jordan", 7);
	ft_strlcpy(&d[20], "aaaa", 5);

	//show_alloc_mem_ex("TINY");
	free(a);
	free(b);
	free(c);
	free(d);
	free(e);
	free(f);
	free(g);
	free(h);
	free(i);
	free(j);
	free(k);
	free(l);
	free(m);
	free(reall);
}
