/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/19 20:24:35 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	ft_printstr(t_list **str)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (*str)
	{
		while (i < (*str)->content_size)
		{
			ft_putchar(((char *)(*str)->content)[i]);
			i++;
			n++;
		}
		i = 0;
		*str = (*str)->next;
	}
	return (n);
}

int		ft_printf(const char *restrict format, ...)
{
	t_list *str;

	str = 0;
	if (ft_readformat(&str, (char *)format) == -1) //получили спискок строк вида строка строка формат строка и т.д.
		{
			//ft_claenup(&str);
			return (0);
		}
	ft_printstr(&str);
	return (100);
}

int		main()
{
	char tmp;

	tmp = 126;
	//  ft_endc();
	ft_printf("well worked %lli");

	//printf("Проверка работы параметров%------R----------------25.25hhd\n", tmp);

	return (0);
}
