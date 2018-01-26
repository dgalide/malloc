/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:13 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/26 18:06:34 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"

void			*malloc_failed(void)
{
	ft_printf("%s\n", strerror(errno));
	return (NULL);
}

static size_t		ft_nbrlen(unsigned long long n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

void				ft_print_addr(int n, int endl)
{
	char				str[ft_nbrlen(n)];
	size_t				len;

	len = ft_nbrlen(n) - 1;
	if (n == 0)
		str[len] = '0';
	str[len + 1] = '\0';
	while (n)
	{
		str[len] = (16 > 10 && n % 16 > 9) ?
			(n % 16) + ('a' - 10) : (n % 16) + 48;
		n /= 16;
		len--;
	}
	ft_putstr("0x");
	if (endl)
		ft_putendl(str);
	else
		ft_putstr(str);
}
