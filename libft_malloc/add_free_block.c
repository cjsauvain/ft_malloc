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

void	add_free_block(t_heap_group *heap, t_block *block)
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
