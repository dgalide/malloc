/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:05 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/22 17:41:38 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"

void			refresh_list(t_large *page)
{
	if (!page->prev && !page->next)
	{
		g_map.larges = NULL;
	}
	else if (!page->prev && page->next)
	{
		page->next->prev = NULL;
		g_map.larges = page->next;
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

	pages = g_map.pages;
	while (pages)
	{
		blocks = pages->blocks;
		while (blocks)
		{
			if ((void *)blocks + sizeof(t_block) == ptr)
			{
				blocks->used = 0;
				return ;
			}
			blocks = blocks->next;
		}
		pages = pages->next;
	}
}

void			get_that_page_out(t_page *page)
{
	if (page->prev && !page->next)
	{
		page->prev->next = NULL;
	}
	else
	{
		page->prev->next = page->next;
		page->next->prev = page->prev;
	}
	munmap(page, g_map.size_page);
}

void			garbage_collector(void)
{
	t_page		*pages;
	t_block		*blocks;
	int			first;
	int			counter;

	pages = g_map.pages;
	first = 1;
	counter = 0;
	while (pages)
	{
		blocks = pages->blocks;
		while (blocks)
		{
			if (blocks->used)
				counter++;
			blocks = blocks->next;
		}
		if (!counter && !first)
			get_that_page_out(pages);
		counter = 0;
		first = 0;
		pages = pages->next;
	}
}

void			free(void *ptr)
{
	t_large		*tmp;

	tmp = NULL;
	if (ptr)
	{
		tmp = g_map.larges;
		while (tmp && (void *)tmp + sizeof(t_large) != (void *)ptr)
			tmp = tmp->next;
		if (tmp)
			refresh_list(tmp);
		else
		{
			reset_small(ptr);
			garbage_collector();
		}
	}
}
