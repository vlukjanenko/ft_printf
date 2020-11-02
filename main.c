#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
//	ft_printf("@moulitest: %#.x %#.0x\n", 0, 0);
//	ft_printf("%*3d|\n", 5, 94827);
	ft_printf("{%f}{%lf}{%Lf}\n", 1.42, 1.42, 1.42l);
	printf("{%f}{%lf}{%Lf}\n", 1.42, 1.42, 1.42l);
//	printf("%*i|\n", -14, 94827);
}
