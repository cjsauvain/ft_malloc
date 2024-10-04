#include "libft_malloc.h"

static t_block	*find_ptr_block(void *ptr)
{
	t_heap	*tmp_heap = g_heap;
	t_block	*tmp_block;

	while (tmp_heap)
	{
		tmp_block = tmp_heap->alloc_block;
		while (tmp_block)
		{
			if ((char *)tmp_block + sizeof(t_block) == ptr)
				return tmp_block;
		}
		tmp_heap = tmp_heap->next;
	}
	return NULL;
}

static void	add_free_block(t_block *ptr_block, size_t realloc_size, size_t aligned_realloc_size)
{
	t_block	*tmp_block;
	t_block	*tmp_free;
	t_block	*next_contiguous_tmpblock;
	t_block	*next_contiguous_tmpfree = tmp_free;

	tmp_free = g_heap->free_block;
	tmp_block = (t_block *)((char *)ptr_block + sizeof(t_block *) + aligned_realloc_size);
	next_contiguous_tmpblock = (t_block *)((char *)ptr_block + sizeof(t_block *) + ptr_block->aligned_size);
	while (tmp_free && tmp_block > tmp_free)
		tmp_free = tmp_free->next;
	if (tmp_free->prev)
		next_contiguous_tmpfree = (t_block *)((char *)tmp_free->prev + sizeof(t_block *) + tmp_free->prev->aligned_size);
	if (next_contiguous_tmpblock == tmp_free)
	{
		tmp_block->next = tmp_free->next;
		tmp_block->prev = tmp_free->prev;
		tmp_block->size = ptr_block->size - realloc_size + tmp_free->size;
		tmp_block->aligned_size = ptr_block->aligned_size - aligned_realloc_size + tmp_free->aligned_size;
		tmp_block->next->prev = tmp_block;
		tmp_block->prev->next = tmp_block;
	}
	else if (next_contiguous_tmpfree == tmp_block)
	{
		tmp_free->prev->size += (ptr_block->size - realloc_size);
		tmp_free->prev->aligned_size += (ptr_block->aligned_size - aligned_realloc_size);
	}
	else if (!tmp_free->prev)
	{
		tmp_free->prev = tmp_block;
		tmp_block->next = tmp_free;
		tmp_block->prev = NULL;
		tmp_block->size = ptr_block->size - realloc_size - sizeof(t_block *);
		tmp_block->aligned_size = ptr_block->aligned_size - aligned_realloc_size - sizeof(t_block *);
	}
	else if (!tmp_free->next)
	{
		tmp_free->prev->next = tmp_block;
		tmp_block->next = tmp_free;
		tmp_free->prev = tmp_block;
		tmp_block->size = ptr_block->size - realloc_size - sizeof(t_block *);
		tmp_block->aligned_size = ptr_block->aligned_size - aligned_realloc_size - sizeof(t_block *);
	}
}


static t_block	*shrink_block(t_block *ptr_block, size_t realloc_size, size_t aligned_realloc_size)
{
	add_free_block(ptr_block, realloc_size, aligned_realloc_size); //tester tous les cas particuliers + revoir implémentation

	ptr_block->size = realloc_size;
	ptr_block->aligned_size = aligned_realloc_size;

	return ptr_block;
}

static void	merge_blocks(t_block *ptr_block, int nb_blocks)
{
	while (ptr_block && nb_blocks - 1)
	{
		ptr_block->prev->size += ptr_block->size + sizeof(t_block *);
		ptr_block->prev->aligned_size += ptr_block->aligned_size + sizeof(t_block *);
		ptr_block->prev->next = ptr_block->next;
		ptr_block = ptr_block->prev;
		nb_blocks--;
	}
}

static void	*extend_block(t_block *ptr_block, size_t realloc_size, size_t aligned_realloc_size)
{
	t_block	*tmp_block;
	void	*new_ptr;
	int		nb_blocks;
	size_t	required_size;

	tmp_block = g_heap->free_block;
	nb_blocks = 0; 
	required_size = 0;
	while (tmp_block)
	{
		if (required_size >= realloc_size)
			break;
		if (!tmp_block-> prev 
			|| (char *)tmp_block->prev + tmp_block->prev->aligned_size + sizeof(t_block *) == (char *)tmp_block)
			required_size += tmp_block->size;
		else
			required_size = 0;
		nb_blocks++;
		tmp_block = tmp_block->next;
	}
	if (required_size >= realloc_size)
	{
		merge_blocks(ptr_block, nb_blocks);
		new_ptr = shrink_block(ptr_block, realloc_size, aligned_realloc_size);
	}
	else
		new_ptr = ft_malloc(realloc_size);
		//enlever ptr_block des blocks alloués et le mettre dans les blocks free
	return new_ptr;
}

static void	*realloc_ptr(t_block *ptr_block, size_t realloc_size)
{
	void	*new_ptr = ptr_block;
	size_t	aligned_realloc_size;

	select_heap(realloc_size);
	aligned_realloc_size = align_mem(realloc_size);
	if (ptr_block->size <= TINY_BLOCK)
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
	}
	//a faire: if realloc_size <= TINY_BLOCK || (realloc_size > TINY_BLOCK && realloc_size <= SMALL_BLOCK)
	if (ptr_block->size > realloc_size)
		new_ptr = shrink_block(ptr_block, realloc_size, aligned_realloc_size);
	else if (ptr_block->size < realloc_size)
		new_ptr = extend_block(ptr_block, realloc_size, aligned_realloc_size);
	return new_ptr;
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr = NULL;
	t_block	*tmp_block;

	if (!ptr)
		new_ptr = ft_malloc(size);
	else if (!size)
		ft_free(ptr);
	else
	{
		tmp_block = find_ptr_block(ptr);
		if (!tmp_block)
			return NULL;
		new_ptr = realloc_ptr(tmp_block, size);
	}
	return new_ptr;
}
