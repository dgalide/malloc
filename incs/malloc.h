#ifndef MALLOC_H
# define MALLOC_H

# include "../srcs/libft/includes/libft.h"
# include <sys/mman.h>
# include <sys/resource.h>
# include <errno.h>
# include <string.h>

# define TINY 10
# define MEDIUM 500

typedef struct 				s_block
{
	int						used;
	int						last;
	int						size;
	struct s_block			*next;
}							t_block;

typedef struct 				s_large
{
	int						size;
	int						total_size;
	struct s_large			*next;
	struct s_large			*prev;
}							t_large;

typedef struct 				s_page
{
	struct s_page			*next;
	struct s_page			*prev;
	t_block					*blocks;
}							t_page;

typedef struct				s_malloc
{
	t_page					*pages;
	t_large					*larges;
	int						size_page;
}							t_malloc;

t_malloc					map;

void 						*ft_malloc(size_t size);
void						ft_free(void *ptr);
void						show_alloc_mem(void);

#endif