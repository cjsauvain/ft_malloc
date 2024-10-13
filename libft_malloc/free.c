#include "libft_malloc.h"

static void	merge_blocks(t_heap_group *heap, t_block *block)
{
	if (block->next)
	{
		if (block->prev)
		{
			block->prev->next = block->next;
			block->next->prev = block->prev;
		}
		else
		{
			block->next->prev = NULL;
			heap->alloc_block = block->next;
		}
	}
	else
	{
		if (block->prev)
			block->prev->next = NULL;
	}
}

void	ft_free(void *ptr) //changer en fonction de t_heap et t_heap_group
{
	t_heap_group	*heap;
	t_block			*block;
	int				status;

	block = (t_block *)((char *)ptr - sizeof(t_block));
	heap = find_heap(block->heap_index, 0);
	while (heap)
	{
		block = heap->alloc_block;
		while (block)
		{
			if ((char *)block + sizeof(t_block) == ptr)
			{
				status = munmap(ptr, block->size);
				if (!status)
					merge_blocks(heap, block);
				return ;
			}
			block = block->next;
		}
		heap = heap->next;
	}
}
