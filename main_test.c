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
}

int			main(void)
{

	char	*a;
	int	 	i;

	i = 0;
	a = (char *)malloc(40);
	a = (char *)malloc(40);
	// ab(a);
	// a = (char *)malloc(40);
	// ab(a);
	// a = malloc(1025);
	show_alloc_mem();
	return 0;
}