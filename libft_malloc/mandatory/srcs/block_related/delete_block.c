#include "libft_malloc_bonus.h"

t_block	*delete_block(t_block *block, size_t size, int merge_req)
{
	t_block	*front_block;

	if (block->size == size)
		front_block = delete_whole_block(block, merge_req);
	else
		front_block = delete_partially(block, size);
	return front_block;
}
