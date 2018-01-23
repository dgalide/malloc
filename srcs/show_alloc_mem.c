/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:13 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/23 15:18:12 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"
#include <stdio.h>

void			show_medium(t_page *page, int *total, int *total_size)
{
	t_page		*tmp;
	t_block		*tmp1;
	int			total_page;
	int			i;

	tmp = page;
	total_page = 0;
	i = 0;
	while (tmp)
	{
		
	}
}

void			show_alloc_mem1(void)
{
	int			total_size;
	int			total;

	total = 0;
	total_size = 0;
	show_large(g_map.larges, &total, &total_size);
	show_medium(g_map.pages, &total, &total_size);
	// ft_printf("%d bytes given\n%d bytes allocated", total_size, total);
}
