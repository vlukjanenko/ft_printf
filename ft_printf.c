/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2020/11/04 01:12:04 by majosue          ###   ########.fr       */
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
	ft_putendl_fd("ERROR", 2);
	exit(0);
}

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

void	ft_printstr(char *str, size_t len, int *n)
{
	static size_t	s_n = 0;
	static char buffer[BUFSIZE + 1] = {0,};

	if (len == 0 || s_n + len > BUFSIZE)
	{
		write(1, buffer, s_n);
		s_n = 0;
		buffer[0] = 0;
	}
	while (len > BUFSIZE)
	{
		write(1, str, len);
		str += len;
		*n += len;
	}
	if (str)
	{
		ft_strncat(&buffer[s_n], str, len);
		s_n += len;
		*n += len;
	}
}

int		ft_printf(const char *restrict format, ...)
{
	//t_list	*str;
	va_list ap;
	int		n;

	n = 0;
	//str = 0;
	va_start(ap, format);
	if (ft_readformat(&n, (char *)format, ap) == -1)
		ft_exit();
	va_end(ap);
	ft_printstr(NULL, 0, &n);
	//str ? ft_lstdel(&str, ft_cleanup) : str;
	return (n);
}
