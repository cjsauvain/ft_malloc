#include "libft_malloc.h"

static void	*realloc_ptr(t_heap_group *heap, t_block *ptr_block, size_t realloc_size)
{
	void	*new_ptr = ptr_block;
	//size_t	aligned_realloc_size;

	/*if (ptr_block->size <= TINY_BLOCK)
	{
		//mettre ptr_block dans les free blocks de cette heap et ft_malloc(realloc_size)
		if (realloc_size > TINY_BLOCK && realloc_size <= SMALL_BLOCK)
		else if (realloc_size > SMALL_BLOCK)
	}
	else if (ptr_block->size > TINY_BLOCK && ptr_block->size <= SMALL_BLOCK)
	{
		//mettre ptr_block dans les free blocks de cette heap et ft_malloc(realloc_size)
		if (realloc_size <= TINY_BLOCK)
		else if (realloc_size > SMALL_BLOCK)
	}
	else
	{
		ft_free(ptr_block);
		if (realloc_size <= SMALL_BLOCK)
			new_ptr = ft_malloc(realloc_size);
	}*/
	if (ptr_block->size > realloc_size)
		new_ptr = shrink_alloc_block(heap, ptr_block, realloc_size);
	else if (ptr_block->size < realloc_size)
		new_ptr = extend_block(heap, ptr_block, realloc_size);
	return new_ptr;
}

void	*ft_realloc(void *ptr, size_t size) // tout modifier en fonction de t_heap et t_heap_group
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
		heap = find_heap(block->heap_index, 0);
		block = find_ptr_block(heap, ptr);
		if (!block)
			return NULL;
		new_ptr = realloc_ptr(heap, block, size);
	}
	return new_ptr;
}
