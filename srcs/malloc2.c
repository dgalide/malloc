/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:13 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/30 16:18:12 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"
#include <stdio.h>

void		setup_page(t_page **page, int size, int alloc_size)
{
	(*page)->prev = NULL;
	(*page)->next = NULL;
	(*page)->total_size = alloc_size;
	(*page)->blocks = (t_block *)((void *)(*page) + sizeof(t_page));
	(*page)->blocks->size = size;
	(*page)->blocks->next = NULL;
	(*page)->blocks->used = 1;
	(*page)->blocks->last = 1;
	(*page)->byte_left = alloc_size - (int)sizeof(t_page);
	(*page)->byte_left -= (size + (int)sizeof(t_block));
}

void		*create_page(int size, int alloc_type)
{
	t_page		*page;
	t_page		*tmp;
	int			alloc_size;

	alloc_size = (alloc_type == T_TINY ? TINY_SIZE : SMALL_SIZE) * PAGE_SIZE;
	tmp = (alloc_type == T_TINY ? g_map.tinies : g_map.smalls);
	page = (t_page *)mmap(0, alloc_size, PROTS, FLAGS, -1, 0);
	if (page == MAP_FAILED)
		return (malloc_failed());
	setup_page(&page, size, alloc_size);
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

void		get_last(t_block **b, t_page **p)
{
	*b = (*p)->blocks;
	while ((*b)->next)
		(*b) = (*b)->next;
}

void		*set_alloc(t_block **b, t_block **new, t_page **p, int alloc_type)
{
	int			size;

	size = (alloc_type == T_TINY ? TINY_SIZE : SMALL_SIZE) * PAGE_SIZE;
	(*b)->next = (t_block *)((void *)(*p) + (size - (*p)->byte_left));
	(*b)->last = 0;
	*new = (*b)->next;
	(*new)->used = 1;
	(*new)->last = 1;
	(*new)->next = NULL;
	return ((void *)*new);
}

void		*update_page(int size, int alloc_type)
{
	t_block		*new;
	t_page		*p;
	t_block		*b;
	void		*tmp;

	b = NULL;
	tmp = NULL;
	p = (alloc_type == T_TINY ? g_map.tinies : g_map.smalls);
	if (!p || (!g_map.tinies && !g_map.smalls))
		return (NULL);
	while (p)
	{
		if ((tmp = check_existing_alloc(size, p)))
			return (tmp);
		if ((p->byte_left - (int)sizeof(t_block)) >= size)
		{
			get_last(&b, &p);
			new = set_alloc(&b, &new, &p, alloc_type);
			new->size = size;
			p->byte_left -= (size + (int)sizeof(t_block));
			return ((void *)new + sizeof(t_block));
		}
		else
			p = p->next;
	}
	return (NULL);
}
