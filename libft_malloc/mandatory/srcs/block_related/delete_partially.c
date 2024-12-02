#include "libft_malloc.h"

static void	update_deleted_part(t_block *block, size_t size)
{
	block->size = size;
	block->aligned_size = ALIGN_MEM(block->size);
}

static t_block	*update_left_part(t_block *block, size_t size)
{
	t_block	*tmp;

	tmp = (t_block *)((char *)block + sizeof(t_block) + ALIGN_MEM(size));
	tmp->size = block->size - size - sizeof(t_block);
	tmp->aligned_size = ALIGN_MEM(tmp->size);
	if (block->prev)
		block->prev->next = tmp;
	if (block->next)
		block->next->prev = tmp;
	tmp->prev = block->prev;
	tmp->next = block->next;
	return tmp;
}

t_block	*delete_partially(t_block *block, size_t size)
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
