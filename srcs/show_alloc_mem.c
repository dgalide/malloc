/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:13 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/24 12:09:33 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"
#include <stdio.h>

// void			show_medium(t_page *page, int *total, int *total_size)
// {
// 	t_page		*tmp;
// 	t_block		*tmp1;
// 	int			total_page;
// 	int			i;

// 	tmp = page;
// 	total_page = 0;
// 	i = 0;
// 	while (tmp)
// 	{
// 		tmp1 = tmp->blocks;

// 	}
// }

int				show_not_larges(int alloc_type)
{
	t_page		*pages;
	t_block		*block;
	int			total;

	total = 0;
	pages = (alloc_type == T_TINY) ? g_map.tinies : g_map.smalls;
	ft_putendl((alloc_type == T_TINY) ? "TINY : " : "SMALL : ");
	// ft_print_addr((int)pages, 1);
	// printf("%p", (void *)pages);
	while (pages)
	{
		block = pages->blocks;
		while (block)
		{
			// ft_printf("");
			ft_print_addr((int)block + sizeof(t_block), 0);
			// ft_printf("%p - %p : \n", (void *)block + sizeof(t_block),\
			// 	(void *)block + sizeof(t_block) + block->size, block->size);
			ft_putstr(" - ");
			ft_print_addr((int)block + sizeof(t_block) + block->size, 0);
			ft_putstr(" : ");
			ft_putnbr(block->size);
			ft_putchar('\n');
			total += block->size;
			block = block->next;
		}
		pages = pages->next;
	}
	return total;
}

void			show_alloc_mem(void)
{
	int			total_size;
	int			total;


	total = 0;
	total_size = 0;
	total += show_not_larges(T_TINY);
	total += show_not_larges(T_SMALL);
	// show_large(g_map.larges, &total, &total_size);
	// show_medium(g_map.pages, &total, &total_size);
	// ft_printf("%d bytes given\n%d bytes allocated", total_size, total);
}
