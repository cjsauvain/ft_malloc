#include "libft_malloc_bonus.h"

t_block	*delete_block(t_block *block, size_t size, int merge_req)
{
	t_block	*front_block;

	/** do implementation over **/
	if (block->size == size 
			|| ((block->size - ALIGN_MEM(size)) < sizeof(t_block) + 16))
		front_block = delete_whole_block(block, merge_req);
	else
		front_block = delete_partially(block, size);
	return front_block;
}
