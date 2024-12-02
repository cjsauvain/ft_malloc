#include "libft_malloc/bonus/include/libft_malloc_bonus.h"
#include <assert.h>
#include <stdint.h>

int main()
{
	void	*ptr;
	size_t	i;

    for (i = 1; i <= 2000; i++)
	{
        ptr = malloc(i);
        if (((uintptr_t)ptr & 15) == 0)
   	    	printf("Allocation of %zu bytes at address %p is aligned\n", i, ptr);
		else
   	    	printf("Allocation of %zu bytes at address %p is not aligned\n", i, ptr);
    }
    return 0;
}
