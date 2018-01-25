#include "incs/malloc.h"

int			main(void)
{

	void	*a;

	a = malloc(40);
	a = malloc(1025);
	show_alloc_mem();
	return 0;
}