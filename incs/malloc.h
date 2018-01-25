/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgalide <dgalide@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 12:33:24 by dgalide           #+#    #+#             */
/*   Updated: 2018/01/24 13:17:49 by dgalide          ###   ########.fr       */
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

# define PRE_ALLOC 105

# define TINY 50
# define MEDIUM 1024
# define SMALL 1024

# define T_SMALL 0
# define T_TINY 1
# define T_LARGE 2

# define TINY_MODULO (TINY * PRE_ALLOC % PAGE_SIZE)
# define TINY_DIVIDE (TINY * PRE_ALLOC / PAGE_SIZE)

# define SMALL_MODULO (SMALL * PRE_ALLOC % PAGE_SIZE)
# define SMALL_DIVIDE (SMALL * PRE_ALLOC / PAGE_SIZE)

# define TINY_SIZE !TINY_MODULO ? TINY_DIVIDE : TINY_DIVIDE + 1
# define SMALL_SIZE !SMALL_MODULO ? SMALL_DIVIDE : SMALL_DIVIDE + 1

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

#endif
