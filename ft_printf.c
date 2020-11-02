/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 04:22:29 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
**	Переписать очищалку
*/

void	ft_cleanup(void *content, size_t content_size)
{
	if (content)
	{
		ft_bzero(content, content_size);
		ft_memdel(&content);
	}
}

int		ft_printstr(t_list *str)
{
	int n;
	t_fmt	*chain;

	if (!str)
		return (0);
	n = 0;
	while (str)
	{
		chain = str->content;
		write(1, chain->str, chain->len);
		n = n + chain->len;
		str = str->next;
	}
	return (n);
}

/* int		ft_format(t_list **str, t_list *begin, va_list ap)
{
	char	tmp;
	t_fun	f;

	begin = *str;
	while (begin)
	{
		if (((char *)begin->content)[0] == '%')
		{
			tmp = ((char *)begin->content)[begin->content_size - 1];
			f = ft_get_f(tmp);
			if (!(f(&begin, ap)))
				return (0);
		}
		begin = begin->next;
	}
	return (1);
} */

int		ft_printf(const char *restrict format, ...)
{
	t_list	*str;
	va_list ap;
	int		n;

	str = 0;
	va_start(ap, format);
	if (ft_readformat(&str, (char *)format, ap) == -1)
	{
		str ? ft_lstdel(&str, ft_cleanup) : str;
		return (0);
	}
	/* if (ft_format(&str, 0, ap) == 0)
	{
		str ? ft_lstdel(&str, ft_cleanup) : str;
		return (0);
	} */
	va_end(ap);
	n = ft_printstr(str);
	str ? ft_lstdel(&str, ft_cleanup) : str;
	return (n);
}

/* int main(void)
{
	ft_printf("%400.10x|\n", 10, 2, 1000);
}
 */
