#include "libft_malloc_bonus.h"

void	merging_blocks(t_block *block)
{
	block->prev->size += (block->next->size + sizeof(t_block));
	block->prev->aligned_size = ALIGN_MEM(block->prev->size);
	block->prev->next = block->next->next;
}

void	link_blocks(t_block *block)
{
	if (block->prev)
		block->prev->next = block->next;
	if (block->next)
		block->next->prev = block->prev;
}

t_block	*delete_whole_block(t_block *block, int merge_req)
{
	size_t	offset;

	offset = 0;
	if (!block->prev && block->next)
	{
		block->next->prev = NULL;
		return block->next;
	}
	else if (!block->prev)
		return NULL;
	if (block->prev)
		offset = block->prev->aligned_size + sizeof(t_block);
	if (merge_req && (char *)block->prev + offset == (char *)block->next)
		merging_blocks(block);
	else
		link_blocks(block);
	while (block && block->prev)
		block = block->prev;
	return block;
}
