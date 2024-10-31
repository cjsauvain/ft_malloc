#include "libft_malloc_bonus.h"

static t_block	*delete_whole_block(t_block *block, int merge_req)
{
	size_t	offset = 0;

	if (!block->prev && block->next)
		block->next->prev = NULL;
	else if (!block->prev)
		return NULL;
	if (block->prev)
		offset = block->prev->aligned_size + sizeof(t_block);
	if (merge_req && (char *)block->prev + offset == (char *)block->next)
	{
		block->prev->size += (block->next->size + sizeof(t_block));
		block->prev->aligned_size = align_mem(block->prev->size);
		block->prev->next = block->next->next;
	}
	else
	{
		if (block->prev)
			block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
	}
	while (block && block->prev)
		block = block->prev;
	return block;
}

static void	update_deleted_part(t_block *block, size_t size)
{
	block->size = size;
	block->aligned_size = align_mem(block->size);
}

static t_block	*update_left_part(t_block *block, size_t size)
{
	t_block	*tmp;

	tmp = (t_block *)((char *)block + sizeof(t_block) + align_mem(size));
	tmp->size = block->size - size;
	tmp->aligned_size = align_mem(tmp->size);
	if (block->prev)
		block->prev->next = tmp;
	if (block->next)
		block->next->prev = tmp;
	tmp->prev = block->prev;
	tmp->next = block->next;
	return tmp;
}

static t_block	*delete_partially(t_block *block, size_t size)
{
	t_block	*tmp;

	tmp = update_left_part(block, size);
	update_deleted_part(block, size);
	if (!tmp->prev)
		return tmp;
	while (block && block->prev)
		block = block->prev;
	return block;
}

t_block	*delete_block(t_block *block, size_t size, int merge_req)
{
	t_block	*front_block;

	if (block->size == size)
		front_block = delete_whole_block(block, merge_req);
	else
		front_block = delete_partially(block, size);
	return front_block;
}
