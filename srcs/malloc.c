/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:13 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/31 13:47:38 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"
#include <stdio.h>

void			set_global(void)
{
	g_map.size_page = PAGE_SIZE;
	g_map.pages = NULL;
	g_map.larges = NULL;
	g_map.tinies = NULL;
	g_map.smalls = NULL;
}

void			*handle_large(int size)
{
	t_large		*ptr;
	t_large		*tmp;
	int			final_size;

	tmp = g_map.larges;
	size += sizeof(t_large);
	final_size = (size % g_map.size_page > 0) ? (size / g_map.size_page + 1) *
	g_map.size_page : size / g_map.size_page * g_map.size_page;
	ptr = (t_large *)mmap(0, final_size, PROTS, FLAGS, -1, 0);
	if (ptr == MAP_FAILED)
		return (malloc_failed());
	ptr->size = size - sizeof(t_large);
	ptr->total_size = final_size;
	ptr->next = NULL;
	ptr->prev = NULL;
	if (!tmp)
		g_map.larges = ptr;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ptr;
		ptr->prev = tmp;
	}
	return ((void *)ptr + sizeof(t_large));
}

void			*handle_tiny_small(size_t size, int alloc_type)
{
	void		*ret;

	if ((ret = update_page(size, alloc_type)))
		return (ret);
	else
		return (create_page(size, alloc_type));
}

void			*malloc(size_t size)
{
	static int	first;
	int			alloc_type;

	alloc_type = (int)size > TINY ? T_SMALL : T_TINY;
	if (first++ == 0)
		set_global();
	if (size <= 0)
		return (NULL);
	if ((int)size <= SMALL)
	{
		return (handle_tiny_small(size, alloc_type));
	}
	else
		return (handle_large(size));
}
