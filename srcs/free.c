#include "../incs/malloc.h"

void 			refresh_list(t_large *page)
{
	if (!page->prev && !page->next)
	{
		map.larges = NULL;
	}
	else if (!page->prev && page->next)
	{
		page->next->prev = NULL;
		map.larges = page->next;
	}
	else if (page->prev && !page->next)
	{
		page->prev->next = NULL;
	}
	else
	{
		page->prev->next = page->next;
		page->next->prev = page->prev;
	}
	munmap(page, page->total_size);
}

void			reset_small(void *ptr)
{
	t_page		*pages;
	t_block		*blocks;

	pages = map.pages;
	while (pages)
	{
		blocks = pages->blocks;
		while (blocks)
		{
			if ((void *)blocks + sizeof(t_block) == ptr)
			{
				blocks->used = 0;
				return;
			}
			blocks = blocks->next;
		}
		pages = pages->next;
	}	
}

void			ft_free(void *ptr)
{
	t_large		*tmp;

	tmp = map.larges;
	while (tmp && (void *)tmp + sizeof(t_large) != (void *)ptr)
		tmp = tmp->next;
	if (tmp)
		refresh_list(tmp);
	else
		reset_small(ptr);
}