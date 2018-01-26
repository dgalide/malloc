/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:38:35 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/26 18:18:24 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"

int				get_size_large(void *ptr)
{
	t_large		*tmp;

	tmp = g_map.larges;
	while (tmp)
	{
		if ((void *)tmp + sizeof(t_large) == ptr)
			return (tmp->size);
		tmp = tmp->next;
	}
	return (0);
}

int				get_size_medium(void *ptr, int first)
{
	t_block		*blocks;
	t_page		*pages;

	pages = first ? g_map.smalls : g_map.tinies;
	while (pages)
	{
		blocks = pages->blocks;
		while (blocks)
		{
			if ((void *)blocks + sizeof(t_block) == ptr)
				return (blocks->size);
			blocks = blocks->next;
		}
		pages = pages->next;
	}
	if (first)
		return get_size_medium(ptr, 0);
	else
		return (0);
}

void			*realloc(void *ptr, size_t size)
{
	void		*tmp;
	void		*new;
	int			old_size;

	tmp = NULL;
	if (!ptr)
		return (malloc(size));
	else if (ptr && size == 0)
	{
		free(ptr);
		return (malloc(1));
	}
	if (!(old_size = get_size_large(ptr)))
		if (!(old_size = get_size_medium(ptr, 1)))
			return (NULL);
	if (old_size > (int)size)
		return (ptr);
	new = malloc(size);
	new = ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}
