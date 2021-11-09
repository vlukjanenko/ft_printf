/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readformat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:10:10 by majosue           #+#    #+#             */
/*   Updated: 2021/07/13 19:24:56 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_save_before_ptr(t_fmt *chain, char **format)
{
	if (chain->percent_sign == *format)
		return (0);
	chain->str = *format;
	chain->len = chain->percent_sign - *format;
	if (ft_printstr(chain->fd, *format, chain->len, chain->n) == -1)
		return (-1);
	*format = chain->percent_sign;
	return (1);
}

int	ft_save_after_ptr(t_fmt *chain, char **format, va_list ap)
{
	t_fun	f;

	chain->percent_sign++;
	if (!ft_chkflags(chain, ap))
	{
		*format = chain->percent_sign;
		return (1);
	}
	f = ft_get_f(chain->modi);
	if (f(chain, ap) == -1)
		return (clean_error_return (chain, -1));
	if (ft_printstr(chain->fd, chain->str, chain->len, chain->n) == -1)
		return (clean_error_return (chain, -1));
	if (chain->str_need_free)
		free(chain->str);
	*format = chain->percent_sign;
	return (1);
}

int	ft_readformat(int fd, int *n, char *format, va_list ap)
{
	t_fmt	chain;
	int		error;

	error = 0;
	ft_bzero(&chain, sizeof(chain));
	chain.fd = fd;
	chain.n = n;
	if (!*format)
		return (0);
	chain.percent_sign = ft_strchr(format, '%');
	if (chain.percent_sign)
	{
		if ((ft_save_before_ptr(&chain, &format)) == -1)
			return (-1);
		if (ft_save_after_ptr(&chain, &format, ap) == -1)
			return (-1);
		error = ft_readformat(chain.fd, n, format, ap);
		return (error);
	}
	chain.str = format;
	chain.len = ft_strlen(format);
	if (ft_printstr(chain.fd, format, chain.len, n) == -1)
		return (-1);
	return (error);
}
