/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/20 21:14:13 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void ft_cleanup(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	free(content);
}

int	ft_printstr(t_list *str)
{
	size_t i;
	int n;

	i = 0;
	n = 0;
	while (str)
	{
		while (i < str->content_size)
		{
			ft_putchar(((char*)str->content)[i]);
			i++;
			n++;
		}
		i = 0;
		str = str->next;
	}
	return (n);
}
int ft_format(t_list **str, t_list *begin, va_list ap)
{
	begin = *str;
	ft_printstr(begin);

return (1);
}
int		ft_printf(const char *restrict format, ...)
{
	t_list *str;
	va_list ap;
	void (*del)(void*, size_t);

	del = &ft_cleanup;
	str = 0;
	if (ft_readformat(&str, (char *)format) == -1) //получили спискок строк вида строка строка формат строка и т.д.
		{
			ft_lstdel(&str,del);
			return (0);
		}
	va_start(ap, format);
	ft_format(&str, 0, ap);
	va_end(ap);
	ft_printstr(str);
	ft_lstdel(&str,del);
	return (100);
}

int		main()
{
	char tmp;

	tmp = 126;
	//  ft_endc();
	ft_printf("well worked %lli", 10);

	//printf("Проверка работы параметров%------R----------------25.25hhd\n", tmp);

	return (0);
}
