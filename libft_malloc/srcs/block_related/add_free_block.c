#include "libft_malloc.h"

static void add_block_in_middle(t_block *block, t_block *tmp)
{
	if ((char *)tmp->prev + tmp->prev->aligned_size + sizeof(t_block) == (char *)block)
	{
		tmp->prev->size += block->size + sizeof(t_block);
		tmp->prev->aligned_size += block->aligned_size + sizeof(t_block);
	}
	else if ((char *)block + block->aligned_size + sizeof(t_block) == (char *)tmp)
	{
		block->size += tmp->size + sizeof(t_block);
		block->aligned_size += tmp->aligned_size + sizeof(t_block);
		block->prev = tmp->prev;
		block->next = tmp->next;
		if (tmp->prev)
			tmp->prev->next = block;
		if (tmp->next)
			tmp->next->prev = block;
	}
	else
	{
		if (tmp->prev)
			tmp->prev->next = block;
		block->next = tmp;
		block->prev = tmp->prev;
		tmp->prev = block;
	}
}

static t_block	*add_block_at_beginning(t_block *block, t_block *tmp)
{
	if ((char *)block + block->aligned_size + sizeof(t_block) == (char *)tmp)
	{
		block->size += tmp->size;
		block->aligned_size += tmp->aligned_size;
		block->next = tmp->next;
		block->prev = NULL;
		if (tmp->next)
			tmp->next->prev = block;
		return block;
	}
	block->next = tmp;
	block->prev = NULL;
	tmp->prev = block;
	return block;
}

static void	add_block_at_end(t_block *block, t_block *tmp)
{
	if ((char *)tmp + tmp->aligned_size + sizeof(t_block) == (char *)block)
	{
		tmp->size += block->size;
		tmp->aligned_size += block->aligned_size;
		return ;
	}
	block->next = NULL;
	block->prev = tmp;
	tmp->next = block;
}

static t_block	*add_block_as_only_block(t_block *block)
{
	block->prev = NULL;
	block->next = NULL;
	return block;
}

void	add_free_block(t_heap_group *heap, t_block *block)
{
	t_block	*tmp;

	tmp = heap->free_block;
	while (tmp && tmp->next && block > tmp)
		tmp = tmp->next;
	if (!tmp)
		heap->free_block = add_block_as_only_block(block);
	else if (tmp && !tmp->prev && block < tmp)
		heap->free_block = add_block_at_beginning(block, tmp);
	else if (tmp && !tmp->next && block > tmp)
		add_block_at_end(block, tmp);
	else
		 add_block_in_middle(block, tmp);
}
