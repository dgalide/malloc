/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:13 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/30 14:48:34 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"

void			print_large(t_large *large)
{
	ft_print_addr((int)large + sizeof(t_large), 0);
	ft_putstr(" - ");
	ft_print_addr((int)large + sizeof(t_large) + large->size, 0);
	ft_putstr(" : ");
	ft_putnbr(large->size);
	ft_putendl(" Bytes");
}

void			print_block(t_block *block)
{
	ft_print_addr((int)block + sizeof(t_block), 0);
	ft_putstr(" - ");
	ft_print_addr((int)block + sizeof(t_block) + block->size, 0);
	ft_putstr(" : ");
	ft_putnbr(block->size);
	ft_putendl(" Bytes");
}

int				show_larges(void)
{
	int			total;
	t_large		*larges;

	total = 0;
	larges = g_map.larges;
	if (larges)
		ft_putendl("LARGES :");
	while (larges)
	{
		total += larges->size;
		print_large(larges);
		larges = larges->next;
	}
	ft_putchar('\n');
	return (total);
}

int				show_not_larges(int alloc_type)
{
	t_page		*pages;
	t_block		*block;
	int			total;

	total = 0;
	pages = (alloc_type == T_TINY) ? g_map.tinies : g_map.smalls;
	if (pages)
		ft_putendl((alloc_type == T_TINY) ? "TINY :" : "SMALL :");
	while (pages)
	{
		block = pages->blocks;
		while (block)
		{
			print_block(block);
			total += block->size;
			block = block->next;
		}
		pages = pages->next;
	}
	return (total);
}

void			show_alloc_mem(void)
{
	int			total_size;
	int			total;

	total = 0;
	total_size = 0;
	total += show_not_larges(T_TINY);
	total += show_not_larges(T_SMALL);
	total += show_larges();
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" Bytes\n");
}
