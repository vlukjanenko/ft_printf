/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2020/11/03 05:13:57 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

const char	g_flag_tab[NBR_FLAGS + 1] =
{' ', '#', '0', '-', '+', '\0'};
const char	g_modi_tab[NBR_MODS + 1] =
{'c', 's', 'p', 'd', 'i', 'o', 'u', 'x', 'X', 'f', '%', '\0'};

void	ft_exit(void)
{
	perror("ERROR");
	exit(0);
}

/*
**	Переписать очищалку
*/

void	ft_cleanup(void *content, size_t content_size)
{
	t_fmt *chain;

	if (content)
	{
		chain = content;
		if (chain->str_need_free)
			free(chain->str);
		ft_bzero(content, content_size);
		ft_memdel(&content);
	}
}

int		ft_printstr(t_list *str)
{
	int		n;
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

int		ft_printf(const char *restrict format, ...)
{
	t_list	*str;
	va_list ap;
	int		n;

	str = 0;
	va_start(ap, format);
	if (ft_readformat(&str, (char *)format, ap) == -1)
		ft_exit();
	va_end(ap);
	n = ft_printstr(str);
	str ? ft_lstdel(&str, ft_cleanup) : str;
	return (n);
}
