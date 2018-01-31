/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:24 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/31 13:48:11 by dgalide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../srcs/libft/includes/libft.h"
# include <sys/mman.h>
# include <sys/resource.h>
# include <errno.h>
# include <string.h>

# define PAGE_SIZE getpagesize()

# define PRE_ALLOC 100

# define TINY PAGE_SIZE / 4
# define SMALL PAGE_SIZE

# define T_SMALL 0
# define T_TINY 1

# define TINY_SIZE TINY * PRE_ALLOC
# define SMALL_SIZE SMALL * PRE_ALLOC

# define FLAGS (MAP_ANON | MAP_PRIVATE)
# define PROTS (PROT_READ | PROT_WRITE | PROT_EXEC)

typedef struct				s_block
{
	int						used;
	int						last;
	int						size;
	struct s_block			*next;
}							t_block;

typedef struct				s_large
{
	int						size;
	int						total_size;
	struct s_large			*next;
	struct s_large			*prev;
}							t_large;

typedef struct				s_page
{
	struct s_page			*next;
	struct s_page			*prev;
	int						byte_left;
	int						total_size;
	t_block					*blocks;
}							t_page;

typedef struct				s_malloc
{
	t_page					*pages;
	t_page					*tinies;
	t_page					*smalls;
	t_large					*larges;
	int						size_page;
}							t_malloc;

t_malloc					g_map;

void						*malloc(size_t size);
void						*realloc(void *ptr, size_t size);
void						free(void *ptr);
void						show_alloc_mem(void);
void						*malloc_failed(void);

void						*create_page(int size, int alloc_type);
void						*update_page(int size, int alloc_type);

void						ft_print_addr(int n, int endl);
void						*check_existing_alloc(int size, t_page *page);

#endif
