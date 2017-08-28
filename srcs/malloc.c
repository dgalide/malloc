#include "../incs/malloc.h"
#include <stdio.h>

void			*malloc_failed(void)
{
	ft_printf("%s\n", strerror(errno));
	return (NULL);
}

void			*handle_large(int size)
{
	t_large		*ptr;
	t_large		*tmp;
	int 		final_size;

	tmp = map.larges;
	size += sizeof(t_large);
	final_size = (size % map.size_page > 0) ? (size / map.size_page + 1) * map.size_page : size / map.size_page * map.size_page;
	ptr = (t_large *)mmap(0, final_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return malloc_failed();
	ptr->size = size - sizeof(t_large);
	ptr->total_size = final_size;
	ptr->next = NULL;
	ptr->prev = NULL;
	if (!tmp)
		map.larges = ptr;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ptr;
		ptr->prev = tmp;
	}
	return (ptr + sizeof(t_large));
}

void			*create_page(t_page *pages, int size)
{
	t_page		*page;
	t_page		*tmp;

	tmp = pages;
	page = (t_page *)mmap(0, map.size_page,\
			PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (page == MAP_FAILED)
		return malloc_failed();
	page->prev = NULL;
	page->next = NULL;
	page->blocks = (t_block *)((void *)page + sizeof(t_page));
	page->blocks->size = size;
	page->blocks->next = NULL;
	page->blocks->used = 1;
	page->blocks->last = 1;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = page;
		page->prev = tmp;
	}
	else
		map.pages = page;
	return ((void *)(page->blocks + sizeof(t_block)));
}

void			*update_page(t_page *pages, int size)
{
	t_block		*new;
	t_page		*p;
	t_block		*b;
	t_block		*prev;
	int			total;

	if (!pages)
		return (NULL);
	p = pages;
	b = p->blocks;
	total = sizeof(t_page);
	while (p)
	{
		while (b)
		{
			prev = b;
			total += (b->size + sizeof(t_block));
			b = b->next;
		}
		if ((int)(map.size_page - total) > (int)(size + sizeof(t_block)))
		{
			prev->next = (t_block *)((void *)p + total);
			prev->last = 0;
			new = prev->next;
			new->size = size;
			new->used = 1;
			new->last = 1;
			return ((void *)new + sizeof(t_block));
		}
		p = p->next;
		total = sizeof(t_page);
	}
	return (NULL);
}

void			*handle_small(t_malloc *map, int size)
{
	void		*ret;

	ret = NULL;
	if ((ret = update_page(map->pages, size)))
		return ret;
	else
		return create_page(map->pages, size);
}

void 			*ft_malloc(size_t size)
{
	static int	first;

	if (first++ == 0)
	{
		map.size_page = getpagesize();
		map.pages = NULL;
		map.larges = NULL;
	}
	if (size == 0)
		return (NULL);
	else
	{
		if (size < MEDIUM)
			return (handle_small(&map, size));
		else
			return (handle_large(size));
	}
}