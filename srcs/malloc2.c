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


void			setup_page(t_page *page, int size)
{
	page->prev = NULL;
	page->next = NULL;
	page->blocks = (t_block *)((void *)page + sizeof(t_page));
	page->blocks->size = size;
	page->blocks->next = NULL;
	page->blocks->used = 1;
	page->blocks->last = 1;
}

void			*create_page(int size, int alloc_type)
{
	t_page		*page;
	t_page		*tmp;
	t_page		*reference;
	int			alloc_size;

	alloc_size = (alloc_type == T_TINY ? TINY_SIZE : SMALL_SIZE);
	tmp = (alloc_type == T_TINY ? g_map.tinies : g_map.smalls);
	reference = tmp;
	page = (t_page *)mmap(0, alloc_size, PROTS, FLAGS , -1, 0);
	if (page == MAP_FAILED)
		return (malloc_failed());
	setup_page(page, size);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = page;
		page->prev = tmp;
	}
	else
		reference = page;
	return ((void *)page->blocks + sizeof(t_block));
}

void			*update_page(t_page *pages, int size, int alloc_type)
{
	t_block		*new;
	t_page		*p;
	t_block		*b;
	t_block		*prev;
	int			total;

	(void)alloc_type;
	if (!pages)
		return (NULL);
	p = pages;
	total = sizeof(t_page);
	while (p)
	{
		b = p->blocks;
		while (b)
		{
			prev = b;
			total += (b->size + sizeof(t_block));
			b = b->next;
		}
		if ((int)(g_map.size_page - total) > (int)(size + sizeof(t_block)))
		{
			prev->next = (t_block *)((void *)p + total);
			prev->last = 0;
			new = prev->next;
			new->size = size;
			new->used = 1;
			new->last = 1;
			new->next = NULL;
			return ((void *)new + sizeof(t_block));
		}
		p = p->next;
		total = sizeof(t_page);
	}
	return (NULL);
}