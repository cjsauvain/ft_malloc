#include "libft_malloc.h"

static void	merge_blocks(t_heap *tmp_heap, t_block *tmp_block)
{
	if (tmp_block->next)
	{
		if (tmp_block->prev)
		{
			tmp_block->prev->next = tmp_block->next;
			tmp_block->next->prev = tmp_block->prev;
		}
		else
		{
			tmp_block->next->prev = NULL;
			tmp_heap->alloc_block = tmp_block->next;
		}
	}
	else
	{
		if (tmp_block->prev)
			tmp_block->prev->next = NULL;
	}
}

void	ft_free(void *ptr)
{
	t_heap	*tmp_heap;
	t_block	*tmp_block;
	int		status;

	tmp_heap = g_heap;
	while (tmp_heap)
	{
		tmp_block = tmp_heap->alloc_block;
		while (tmp_block)
		{
			if ((char *)tmp_block + sizeof(t_block) == ptr)
			{
				status = munmap(ptr, tmp_block->size);
				if (!status)
					merge_blocks(tmp_heap, tmp_block);
				return ;
			}
			tmp_block = tmp_block->next;
		}
		tmp_heap = tmp_heap->next;
	}
}
