/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readformat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:10:10 by majosue           #+#    #+#             */
/*   Updated: 2020/11/04 00:55:33 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_save_before_ptr(int *n, char **ptr, char **format)
{
	t_fmt	chain;

	ft_bzero(&chain, sizeof(chain));
	if (*ptr == *format)
		return (0);
	chain.str = *format;
	chain.len = *ptr - *format;
	ft_printstr(*format, chain.len, n);
	*format = *ptr;
	return (1);
}

int	ft_save_after_ptr(int *n, char **ptr, char **format, va_list ap)
{
	t_fmt	chain;
	t_fun	f;

	ft_bzero(&chain, sizeof(chain));
	(*ptr)++;
	if (!ft_chkflags(ptr, &chain, ap))
	{
		*format = *ptr;
		return (1);
	}
	f = ft_get_f(chain.modi);
	f(&chain, ap);
	ft_printstr(chain.str, chain.len, n);
	if (chain.str_need_free)
		free(chain.str);
	*format = *ptr;
	return (1);
}

int	ft_readformat(int *n, char *format, va_list ap)
{
	char	*ptr;
	t_fmt	chain;

	ft_bzero(&chain, sizeof(chain));
	if (!*format)
		return (0);
	if ((ptr = ft_strchr(format, '%')))
	{
		if ((ft_save_before_ptr(n, &ptr, &format)) == -1)
			return (-1);
		if (ft_save_after_ptr(n, &ptr, &format, ap) == -1)
			return (-1);
		return (ft_readformat(n, format, ap));
	}
	chain.str = format;
	chain.len = ft_strlen(format);
	ft_printstr(format, chain.len, n);
	return (1);
}
