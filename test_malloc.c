#include "libft_malloc/mandatory/include/libft_malloc.h"

int	main(void)
{
	char	*str;
	int		i = 0;

	while (i < 1024)
	{
		str = malloc(1024 * sizeof(char));
		if (!str)
			continue ;
		str[0] = 'a';
		//free(str);
		i++;
	}
}
