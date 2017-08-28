#include "incs/malloc.h"

int main(int ac, char **av)
{
	char *ptr = (char *)ft_malloc(501);
	char *ptr11 = (char *)ft_malloc(23455);
	char *ptr1 = (char *)ft_malloc(450);
	char *ptr2 = (char *)ft_malloc(450);
	char *ptr3 = (char *)ft_malloc(450);
	char *ptr4 = (char *)ft_malloc(450);
	char *ptr5 = (char *)ft_malloc(450);
	char *ptr6 = (char *)ft_malloc(450);
	char *ptr7 = (char *)ft_malloc(450);
	char *ptr8 = (char *)ft_malloc(450);
	char *ptr9 = (char *)ft_malloc(450);
	char *ptr10 = (char *)ft_malloc(450);
	int i = -1;
	while (++i < 440)
	{
		ptr8[i] = 42;
	}
	// ft_putendl(ptr);
	// ft_putendl(ptr1);
	show_alloc_mem();
	return (0);
}