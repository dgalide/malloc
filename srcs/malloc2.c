/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:13 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/24 14:27:44 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"
#include <stdio.h>

void			setup_page(t_page **page, int size)
{
	(*page)->prev = NULL;
	(*page)->next = NULL;
	(*page)->blocks = (t_block *)((void *)(*page) + sizeof(t_page));
	(*page)->blocks->size = size;
	(*page)->blocks->next = NULL;
	(*page)->blocks->used = 1;
	(*page)->blocks->last = 1;
}

void			*create_page(int size, int alloc_type)
{
	t_page		*page;
	t_page		*tmp;
	int			alloc_size;

	alloc_size = (alloc_type == T_TINY ? TINY_SIZE : SMALL_SIZE);
	tmp = (alloc_type == T_TINY ? g_map.tinies : g_map.smalls);
	page = (t_page *)mmap(0, alloc_size, PROTS, FLAGS , -1, 0);
	if (page == MAP_FAILED)
		return (malloc_failed());
	setup_page(&page, size);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = page;
		page->prev = tmp;
	}
	else
	{
		if (alloc_type == T_TINY)
			g_map.tinies = page;
		else
			g_map.smalls = page;
	}
	return ((void *)page->blocks + sizeof(t_block));
}

void			get_total(int *total, t_block **b, t_page **p)
{
	*b = (*p)->blocks;
	*total = 0;
	while ((*b)->next)
	{
		*total += ((*b)->size + sizeof(t_block));
		(*b) = (*b)->next;
	}
	*total += ((*b)->size + sizeof(t_block));
}

void 			*set_alloc(t_block **b, t_block **new, t_page **p, int total)
{
	(*b)->next = (t_block *)((void *)(*p) + total);
	(*b)->last = 0;
	*new = (*b)->next;
	(*new)->used = 1;
	(*new)->last = 1;
	(*new)->next = NULL;
	return ((void *)*new);
}

void			*update_page(int size, int alloc_type)
{
	t_block		*new;
	t_page		*p;
	t_block		*b;
	int			total;

	new = NULL;
	b = NULL;
	p = (alloc_type == T_TINY ? g_map.tinies : g_map.smalls);
	if (!p || (!g_map.tinies && !g_map.smalls))
		return (NULL);
	total = sizeof(t_page);
	while (p)
	{
		get_total(&total, &b, &p);
		if ((int)(PAGE_SIZE - total) > (int)(size + sizeof(t_block)))
		{
			new = set_alloc(&b, &new, &p, total);
			new->size = size;
			return ((void *)new + sizeof(t_block));
		}
		p = p->next;
		total = sizeof(t_page);
	}
	return (NULL);
}