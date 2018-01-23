void			show_large(t_large *large, int *total, int *total_size)
{
	t_large 	*tmp;

	tmp = large;
	(void)total;
	(void)total_size;
	while (tmp)
	{
		ft_printf("LARGE :\n\tWANTED -> %p - %p : %d bytes\n\tGIVEN -> %p - %p : %d bytes\n\t-- %d dedicated to malloc\n\t-- %d remaining bytes\n\t-- page size : %d\n",
			(void *)tmp + sizeof(t_large),
			(void *)tmp + sizeof(t_large) + tmp->size,
			tmp->size,
			(void *)tmp,
			(void *)tmp + tmp->total_size,
			tmp->total_size,
			(int)sizeof(t_large),
			(int)(tmp->total_size - tmp->size - sizeof(t_large)),
			g_map.size_page);
		// *total_size += tmp->size;
		// *total += tmp->total_size;
		tmp = tmp->next;
	}
}

void			show_tiny(t_block *tmp)
{
	ft_printf("\tTINY :\n\t\tWANTED -> %p - %p : %d bytes\n\t\tGIVEN -> %p - %p : %d bytes\n\t\t-- %d dedicated to malloc\tUsed : %d\n",
			(void *)tmp + sizeof(t_block), (void *)tmp + sizeof(t_block) + tmp->size, tmp->size,
			(void *)tmp, (void *)tmp + sizeof(t_block) + tmp->size, (int)(sizeof(t_block)) + tmp->size, (int)(sizeof(t_block)), tmp->used);
}

void			show_small(t_block *tmp)
{
	ft_printf("\tSMALL :\n\t\tWANTED -> %p - %p : %d bytes\n\t\tGIVEN -> %p - %p : %d bytes\n\t\t-- %d dedicated to malloc\tUsed : %d\n",
			(void *)tmp + sizeof(t_block), (void *)tmp + (int)(sizeof(t_block)) + tmp->size, tmp->size,
			(void *)tmp, (void *)tmp + sizeof(t_block) + tmp->size, (int)(sizeof(t_block)) + tmp->size, (int)(sizeof(t_block)), tmp->used);
}

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
		tmp1 = tmp->blocks;
		ft_printf("PAGE %d : %p\n", i++, tmp);
		while (tmp1)
		{
			total_page += tmp1->size;
			if (tmp1->size < TINY)
				show_tiny(tmp1);
			else
				show_small(tmp1);
			tmp1 = tmp1->next;
		}
		ft_printf("\n\tTotal given : %d Bytes\n", total_page);
		*total_size += total_page;
		*total += g_map.size_page;
		total_page = 0;
		tmp = tmp->next;
	}
}