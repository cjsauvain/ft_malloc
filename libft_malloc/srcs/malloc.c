#include "libft_malloc.h"

t_heap			g_heap;
pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

static t_heap_group	*get_heap(size_t size)
{
	t_heap_group	*heap;
	int				heap_state;

	heap_state = check_heap_state(size);
	if (!heap_state)
		heap = create_heap(size);
	else
	{
		heap = check_heap_left(size);
		if (!heap)
			heap = add_heap(size);
	}
	return heap;
}

void	*malloc(size_t size)
{
	t_heap_group	*heap;
	void			*block;

	pthread_mutex_lock(&g_mutex);
	heap = NULL;
	if (!size)
	{
		pthread_mutex_unlock(&g_mutex);
		return NULL;
	}
	heap = get_heap(size);
	if (!heap)
	{
		pthread_mutex_unlock(&g_mutex);
		return NULL;
	}
	block = get_avail_block(heap, size);
	pthread_mutex_unlock(&g_mutex);
	return block;
}
