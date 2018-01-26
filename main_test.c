#include "incs/malloc.h"


void		ab(char *a)
{
	int i;

	i = 0;
	while (i < 40)
	{
		a[i] = 42;
		i++;
	}
	a[i -1] = 0;
}

int			main(void)
{

	char	*a;
	char	*b;
	int	 	i;

	i = 0;
	a = (char *)malloc(40);
	b = (char *)malloc(40);
	ab(a);
	ab(b);
	ft_putendl(a);
	ft_putendl(b);
	// a = (char *)malloc(40);
	// ab(a);
	// a = malloc(1025);
	show_alloc_mem();
	return 0;
}