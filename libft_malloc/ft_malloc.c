#include "ft_malloc.h"

void	*ft_malloc(size_t size)
{
	static t_heap	*heap;
	t_block			*alloc_block;
	size_t			aligned_size;

	aligned_size = align4(size);
	if (check_heap_state(heap, aligned_size))
		heap = create_new_heap(heap, aligned_size);
	alloc_block = get_avail_block(heap, aligned_size);
	
	return (void *)alloc_block;
}
/*
#include <stdio.h> //A SUPPRIMER!!!!!

int	main(void)
{
	char	*p = ft_malloc(1 * sizeof(char));
	char	*s = ft_malloc(5 * sizeof(char));
	int		i = 0;

	p[0] = 'a';
	p[1] = 'a';
	p[2] = 'a';
	while (i < 5)
		s[i++] = '1';
	printf("%s\n", s);
	printf("adresse de p: %p\n", p);
	printf("adresse de s: %p\n", s);
	printf("%s\n", s);
}


int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	uint8_t	*pi = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (pi == MAP_FAILED)
		return (1);
	//VALGRIND_MALLOCLIKE_BLOCK(pi, sizeof(pi), 0, 0);
	printf("%p\n", pi);
	munmap(pi, 4096);
	//VALGRIND_FREELIKE_BLOCK(pi, 0);
	return (0);
}*/
