#include "incs/malloc.h"

int main(int ac, char **av)
{
	char *ptr = ft_malloc(501);
	// ft_printf("\nptr = %p\n", (void *)ptr);
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
	char *ptr12 = (char *)ft_malloc(450);
	char *ptr13 = (char *)ft_malloc(450);
	int i = -1;
	while (++i < 440)
	{
		ptr10[i] = 42;
	}
	// ft_putendl(ptr);
	// ft_putendl(ptr1);
	show_alloc_mem();
	ft_free(ptr);
	ft_free(ptr9);
	ft_free(ptr3);
	char *ptr14 = (char *)ft_malloc(300);
	ft_printf("\nptr = %p\n", (void *)ptr);
	show_alloc_mem();
	return (0);
}