/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:05 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/30 16:19:46 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"
#include <stdio.h>

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

void			reset_small(void *ptr, int first)
{
	t_page		*pages;
	t_block		*blocks;

	pages = first ? g_map.tinies : g_map.smalls;
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
	if (first)
		reset_small(ptr, 0);
}

void			get_that_page_out(t_page *page, int boo)
{
	if (!page->prev && !page->next)
	{
		if (boo)
			g_map.tinies = NULL;
		else
			g_map.smalls = NULL;
	}
	else if (!page->prev && page->next)
	{
		page->next->prev = NULL;
		if (boo)
			g_map.tinies = (g_map.tinies)->next;
		else
			g_map.smalls = (g_map.smalls)->next;
	}
	if (page->prev && !page->next)
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

void			garbage_collector(int boo)
{
	t_page		*pages;
	t_block		*blocks;
	int			counter;

	pages = boo ? g_map.tinies : g_map.smalls;
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
		if (!counter)
			get_that_page_out(pages, boo);
		counter = 0;
		pages = pages->next;
	}
	if (boo)
		garbage_collector(0);
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
			reset_small(ptr, 1);
			garbage_collector(1);
		}
	}
}
