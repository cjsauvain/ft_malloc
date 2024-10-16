#include "libft_malloc.h"

static int merge_two_consecutive_block_if_necessary(t_block *block, t_block *tmp)
{
	if (tmp && tmp->prev 
		&& (char *)tmp->prev + tmp->prev->aligned_size + sizeof(t_block) == (char *)block)
	{
		tmp->prev->size += block->size + sizeof(t_block);
		tmp->prev->aligned_size += block->aligned_size + sizeof(t_block);
		return 1;
	}
	else if (tmp
		&& (char *)tmp + tmp->aligned_size + sizeof(t_block) == (char *)block)
	{
		block->size += tmp->size + sizeof(t_block);
		block->aligned_size += tmp->aligned_size + sizeof(t_block);
		block->prev = tmp->prev;
		block->next = tmp->next;
		if (tmp->prev)
			tmp->prev->next = block;
		if (tmp->next)
			tmp->next->prev = block;
		return 1;
	}
	return 0;
}

static int	add_block_at_beginning_if_necessary(t_heap_group *heap, t_block *block, t_block *tmp, int merged)
{
	if (!merged && tmp && !tmp->prev)
	{
		if (block < tmp)
		{
			tmp->prev = block;
			block->next = tmp;
			block->prev = NULL;
			heap->free_block = block;
		}
		else
		{
			if (tmp->next)
				tmp->next->prev = block;
			block->next = tmp->next;
			block->prev = tmp;
			tmp->next = block;
		}
		return 1;
	}
	return 0;
}

static int	add_block_at_end_if_necessary(t_heap_group *heap, t_block *block, t_block *tmp, int position)
{
	if (!position && tmp && !tmp->next)
	{
		if (block < tmp)
		{
			tmp->prev = block;
			block->next = tmp;
			block->prev = NULL;
			heap->free_block = block;
		}
		else
		{
			if (tmp->next)
				tmp->next->prev = block;
			block->next = tmp->next;
			block->prev = tmp;
			tmp->next = block;
		}
		return 1;
	}
	return position;
}

static void	add_free_block(t_heap_group *heap, t_block *block)
{
	t_block	*tmp;
	int		merged;
	int		position;

	tmp = heap->free_block;
	while (tmp && tmp->next && block > tmp)
		tmp = tmp->next;
	merged = merge_two_consecutive_block_if_necessary(block, tmp);
	position = add_block_at_beginning_if_necessary(heap, block, tmp, merged);
	position = add_block_at_end_if_necessary(heap, block, tmp, merged);
	if (!position)
	{
		tmp->prev->next = block;
		block->prev = tmp->prev;
		block->next = tmp;
		tmp->prev = block;
	}
}

static t_block	*shrink_alloc_block(t_heap_group *heap, t_block *ptr_block, size_t realloc_size)
{
	t_block	*freed_block;
	size_t	aligned_realloc_size;

	aligned_realloc_size = align_mem(realloc_size);
	freed_block = (t_block *)((char *)ptr_block + sizeof(t_block) + aligned_realloc_size);
	freed_block->size = ptr_block->size - realloc_size - sizeof(t_block);
	freed_block->aligned_size = ptr_block->aligned_size - aligned_realloc_size - sizeof(t_block);
	add_free_block(heap, freed_block); //tester tous les cas particuliers + revoir implémentation

	ptr_block->size = realloc_size;
	ptr_block->aligned_size = align_mem(realloc_size);

	return ptr_block;
}

static void	put_realloc_block_before_alloc_block(t_block *realloc_block, t_block *alloc_block)
{
	if (!alloc_block->prev)
	{
		alloc_block->prev = realloc_block;
		realloc_block->next = alloc_block;
		realloc_block->prev = NULL;
	}
	else
	{
		realloc_block->next = alloc_block;
		realloc_block->prev = alloc_block->prev;
		alloc_block->prev->next = realloc_block;
		alloc_block->prev = realloc_block;
	}
}

static void	put_realloc_block_after_alloc_block(t_block *realloc_block, t_block *alloc_block)
{
	if (!alloc_block->next)
	{
		alloc_block->next = realloc_block;
		realloc_block->prev = alloc_block;
		realloc_block->next = NULL;
	}
	else
	{
		realloc_block->next = alloc_block->next;
		realloc_block->prev = alloc_block;
		alloc_block->next->prev = realloc_block;
		alloc_block->next = realloc_block;
	}
}

static void	add_alloc_block(t_block *alloc_block, t_block *realloc_block)
{
	while (alloc_block && alloc_block->next && realloc_block > alloc_block)
		alloc_block = alloc_block->next;
	if (realloc_block < alloc_block)
		put_realloc_block_before_alloc_block(realloc_block, alloc_block);
	else
		put_realloc_block_after_alloc_block(realloc_block, alloc_block);
}

static void	remove_ptr_block(t_heap_group *heap, t_block *ptr_block)
{
	if (!ptr_block->prev)
	{
		heap->alloc_block = ptr_block->next;
		if (ptr_block->next)
			ptr_block->next->prev = NULL;
	}
	else if (!ptr_block->next)
	{
		if (ptr_block->prev)
			ptr_block->prev->next = NULL;
	}
	else
	{
		ptr_block->prev->next = ptr_block->next;
		ptr_block->next->prev = ptr_block->prev;
	}
}

static t_block	*shrink_free_block(t_heap_group *heap, t_block *ptr_block, t_block *realloc_block, size_t realloc_size)
{
	t_block	*tmp_block;
	size_t	aligned_realloc_size;

	aligned_realloc_size = align_mem(realloc_size);
	tmp_block = (t_block *)((char *)realloc_block + sizeof(t_block) + aligned_realloc_size);
	tmp_block->size = realloc_block->size - realloc_size - sizeof(t_block);
	tmp_block->aligned_size = realloc_block->aligned_size - aligned_realloc_size - sizeof(t_block);
	heap->free_block = tmp_block;
	realloc_block->size = realloc_size;
	realloc_block->aligned_size = align_mem(realloc_size);

	add_alloc_block(heap->alloc_block, realloc_block); //tester tous les cas particuliers + revoir implémentation
	remove_ptr_block(heap, ptr_block);

	return realloc_block;
}

static void	merge_blocks(t_block *block, size_t required_size)
{
	if (block->size == required_size)
		return ;
	required_size -= block->size;
	while (block && required_size)
	{
		block->prev->size += block->size + sizeof(t_block);
		block->prev->aligned_size += block->aligned_size + sizeof(t_block);
		block->prev->next = block->next;
		block = block->prev;
		required_size -= block->size;
	}
}

static size_t	get_required_size(t_block *tmp, size_t realloc_size)
{
	size_t	required_size;

	required_size = 0;
	while (tmp)
	{
		if (!tmp-> prev 
			|| (char *)tmp->prev + tmp->prev->aligned_size + sizeof(t_block) == (char *)tmp)
			required_size += tmp->size;
		else
			required_size = 0;
		if (required_size >= realloc_size)
			return required_size;
		tmp = tmp->next;
	}
	return 0;
}

static void	*extend_block(t_heap_group *heap, t_block *ptr_block, size_t realloc_size)
{
	t_block	*free_block;
	void	*new_ptr;
	size_t	required_size;

	free_block = heap->free_block;
	required_size = get_required_size(free_block, realloc_size);
	if (required_size >= realloc_size)
	{
		merge_blocks(free_block, required_size);
		new_ptr = shrink_free_block(heap, ptr_block, free_block, realloc_size);
	}
	else
	{
		new_ptr = ft_malloc(realloc_size);
		ptr_block->prev->next = ptr_block->next; //ajouter condition if (ptr_block->prev)
		ptr_block->next->prev = ptr_block->prev; //ajouter condition if (ptr_block->next)
	}
	add_free_block(heap, ptr_block); //tester tous les cas particuliers + revoir implémentation
	return new_ptr;
}

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
