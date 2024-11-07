#include "libft_malloc_bonus.h"

t_heap	g_heap;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*ft_malloc(size_t size)
{
	t_heap_group	*heap;
	void			*block;
	int				heap_state;

	pthread_mutex_lock(&g_mutex);
	heap = NULL;
	if (!size)
		return NULL;
	heap_state = check_heap_state(size);
	if (!heap_state)
		heap = create_heap(size);
	else
	{
		heap = check_heap_left(size);
		if (!heap)
			heap = add_heap(size);
	}
	if (!heap)
		return NULL;
	block = get_avail_block(heap, size);
	pthread_mutex_unlock(&g_mutex);
	return block;
}
