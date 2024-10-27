#include "libft_malloc.h"

static int	check_rezone_necessity(size_t size_ptr, size_t size_realloc)
{
	if (size_ptr <= TINY_BLOCK && size_realloc > TINY_BLOCK)
		return 1;
	if (size_ptr > TINY_BLOCK && size_ptr <= SMALL_BLOCK
		&& (size_realloc > SMALL_BLOCK || size_realloc <= TINY_BLOCK))
		return 1;
	if (size_ptr > SMALL_BLOCK && size_realloc <= SMALL_BLOCK)
		return 1;
	return 0;
}

static void	*realloc_ptr(t_heap_group *heap, t_block *ptr_block, size_t realloc_size)
{
	void	*new_ptr = ptr_block;

	if (ptr_block->size > realloc_size)
		new_ptr = shrink_alloc_block(heap, ptr_block, realloc_size);
	else if (ptr_block->size < realloc_size)
		new_ptr = extend_block(heap, ptr_block, realloc_size);
	return new_ptr;
}

static void	*rezone_allocation(void *ptr, size_t size)
{
	void	*new_ptr;

	ft_free(ptr);
	new_ptr = ft_malloc(size);

	return new_ptr;
}

void	*ft_realloc(void *ptr, size_t size)
{
	void			*new_ptr = NULL;
	t_block			*block;
	t_heap_group	*heap;

	if (!ptr)
		new_ptr = ft_malloc(size);
	else if (!size)
		ft_free(ptr);
	else
	{
		block = (t_block *)((char *)ptr - sizeof(t_block));
		heap = find_heap(block, 0);
		if (!heap)
			return NULL;
		if (check_rezone_necessity(block->size, size))
			new_ptr = rezone_allocation(ptr, size);
		else
			new_ptr = realloc_ptr(heap, block, size);
	}
	return new_ptr;
}
