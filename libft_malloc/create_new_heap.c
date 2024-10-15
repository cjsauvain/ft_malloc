#include "libft_malloc.h"

static int	get_new_index(int index, int i)
{
	t_heap_group	*tmp_heaps;

	if (i == 0)
		tmp_heaps = g_heap.tiny_heap;
	else if (i == 1)
		tmp_heaps = g_heap.small_heap;
	else if (i == 2)
		tmp_heaps = g_heap.large_heap;
	while (tmp_heaps)
	{
		if (tmp_heaps->index > index)
			index = tmp_heaps->index;
		tmp_heaps = tmp_heaps->next;
	}
	if (i < 2)
		index = get_new_index(index, i + 1);
	if (!index)
		return 1;
	return index;
}

static void	initialize_new_heap(t_heap_group *new_heap, size_t alloc_size, size_t size)
{
	size_t	aligned_alloc_size;

	aligned_alloc_size = align_mem(alloc_size);

	new_heap->index = get_new_index(0, 0);
	new_heap->aligned_size = aligned_alloc_size;
	new_heap->alloc_block = NULL;
	new_heap->prev = NULL;
	new_heap->next = NULL;
	if (size > SMALL_BLOCK)
	{
		new_heap->free_block = NULL;
		return ;
	}
	if (alloc_size != (size_t)TINY_HEAP && alloc_size != (size_t)SMALL_HEAP)
	{
		new_heap->free_block = NULL;
		return ;
	}
	new_heap->free_block = (t_block *)((char *)new_heap + sizeof(t_heap_group));
	new_heap->free_block->heap_index  = new_heap->index;
	new_heap->free_block->size = alloc_size - sizeof(t_block) - sizeof(t_heap_group);
	new_heap->free_block->aligned_size = aligned_alloc_size - sizeof(t_block) - sizeof(t_heap_group);
	new_heap->free_block->next = NULL;
	new_heap->free_block->prev = NULL;
}

static size_t	get_alloc_size(size_t size)
{
	if (size <= TINY_BLOCK)
		return TINY_HEAP;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		return SMALL_HEAP;
	return (size + sizeof(t_heap));
}

static t_heap_group	*create_heap(size_t size)
{
	t_heap_group	*new_heap;
	size_t			alloc_size;

	alloc_size = get_alloc_size(size);
	new_heap = mmap(NULL, align_mem(alloc_size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (new_heap == MAP_FAILED)
		return NULL;
	initialize_new_heap(new_heap, alloc_size, size);
	if (size <= TINY_BLOCK)
		g_heap.tiny_heap = new_heap;
	else if (size > TINY_BLOCK && size <= SMALL_BLOCK)
		g_heap.small_heap = new_heap;
	else
		g_heap.large_heap = new_heap;
	return new_heap;
}

static int	add_heap_edge(t_heap_group *heaps, t_heap_group *new_heap)
{
	if (heaps && !heaps->prev && new_heap < heaps)
	{
		new_heap->prev = NULL;
		new_heap->next = heaps;
		heaps->prev = new_heap;
		return 1;
	}
	else if (heaps && !heaps->next && new_heap > heaps)
	{
		new_heap->next = NULL;
		new_heap->prev = heaps;
		heaps->next = new_heap;
		return 1;
	}
	return 0;
}

static void	add_heap_middle(t_heap_group *heaps, t_heap_group *new_heap, int add_status)
{
	if (!add_status && new_heap < heaps)
	{
		new_heap->prev = heaps->prev;
		new_heap->next = heaps;
		heaps->prev->next = new_heap;
		heaps->prev = new_heap;
	}
	else if (!add_status && new_heap > heaps)
	{
		new_heap->prev = heaps;
		new_heap->next = heaps->next;
		heaps->next->prev = new_heap;
		heaps->next = new_heap;
	}
}

static void	add_new_heap(t_heap_group *new_heap, size_t alloc_size, size_t size)
{
	t_heap_group	*heaps;
	int				add_status;

	heaps = select_heap(size);
	while (heaps && heaps->next && new_heap > heaps)
		heaps = heaps->next;
	if (heaps)
	{
		initialize_new_heap(new_heap, alloc_size, size);
		add_status = add_heap_edge(heaps, new_heap);
		add_heap_middle(heaps, new_heap, add_status);
	}
}

static t_heap_group	*check_if_heap_contiguous(t_heap_group *new_heap, size_t alloc_size, size_t size)
{
	t_heap_group	*heaps;

	heaps = select_heap(size);
	while (heaps)
	{
		if ((char *)new_heap + alloc_size == (char *)heaps)
			return heaps;
		else if ((char *)heaps + heaps->aligned_size + sizeof(t_heap_group) == (char *)new_heap)
			return heaps;
		heaps = heaps->next;
	}
	return NULL;
}

static void	add_new_heap_free_blocks(t_heap_group *heap_pos, t_heap_group *new_heap, size_t alloc_size)
{
	t_block	*tmp_free;
	size_t	aligned_alloc_size;

	tmp_free = heap_pos->free_block;
	while (tmp_free && tmp_free->next)
		tmp_free = tmp_free->next;
	if (tmp_free)
	{
		aligned_alloc_size = align_mem(alloc_size);
		tmp_free->next = (t_block *)new_heap;
		tmp_free->next->prev = tmp_free;
		tmp_free->next->next = NULL;
		tmp_free->next->size = alloc_size - sizeof(t_block);
		tmp_free->next->aligned_size = aligned_alloc_size - sizeof(t_block);
		tmp_free->next->heap_index = heap_pos->index;
		heap_pos->aligned_size += aligned_alloc_size;
	}
}

static void	add_heap_pos_free_blocks(t_heap_group *heap_pos, t_heap_group *new_heap, size_t alloc_size)
{
	size_t	aligned_alloc_size;

	if (heap_pos->prev)
		heap_pos->prev->next = new_heap;
	if (heap_pos->next)
		heap_pos->next->prev = new_heap;

	aligned_alloc_size = align_mem(alloc_size);
	*new_heap = *heap_pos;
	new_heap->aligned_size += aligned_alloc_size;
	new_heap->free_block = (t_block *)((char *)new_heap + sizeof(t_heap_group));
	new_heap->free_block->heap_index = heap_pos->index;
	new_heap->free_block->size = alloc_size - sizeof(t_heap_group) - sizeof(t_block);
	new_heap->free_block->aligned_size = aligned_alloc_size - sizeof(t_heap_group) - sizeof(t_block);
	new_heap->free_block->next = heap_pos->free_block;
	new_heap->free_block->prev = NULL;
	heap_pos->free_block->prev = new_heap->free_block;
}

static t_heap_group	*merge_heaps(t_heap_group *heap_pos, t_heap_group *new_heap, size_t alloc_size)
{
	if (heap_pos < new_heap)
	{
		add_new_heap_free_blocks(heap_pos, new_heap, alloc_size);
		return heap_pos;
	}
	add_heap_pos_free_blocks(heap_pos, new_heap, alloc_size);
	return new_heap;
}

static t_heap_group	*add_heap(size_t size)
{
	t_heap_group	*new_heap;
	t_heap_group	*heap_pos;
	size_t			alloc_size;

	alloc_size = get_alloc_size(size);
	new_heap = mmap(NULL, align_mem(alloc_size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	if (new_heap == MAP_FAILED)
		return NULL;
	if (size <= SMALL_BLOCK)
	{
		heap_pos = check_if_heap_contiguous(new_heap, alloc_size, size);
		if (heap_pos)
		{
			new_heap = merge_heaps(heap_pos, new_heap, alloc_size);
			return new_heap;
		}
	}
	add_new_heap(new_heap, alloc_size, size);
	return new_heap;
}

t_heap_group	*allocate_heap(size_t size, int mode)
{
	t_heap_group	*heap;

	if (mode)
		heap = add_heap(size);
	else
		heap = create_heap(size);
	return heap;
}
