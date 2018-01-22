/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:38:35 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/22 16:52:25 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/malloc.h"

void			*realloc(void *ptr, size_t size)
{
	if (size > 0)
	{
		free(ptr);
		return (malloc(size));
	}
	return (NULL);
}