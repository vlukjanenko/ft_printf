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

int	ft_save_before_ptr(t_fmt *chain, char **format)
{
	if (chain->percent_sign == *format)
		return (0);
	chain->str = *format;
	chain->len = chain->percent_sign - *format;
	ft_printstr(chain->fd, *format, chain->len, chain->n);
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
	f(chain, ap);
	ft_printstr(chain->fd, chain->str, chain->len, chain->n);
	if (chain->str_need_free)
		free(chain->str);
	*format = chain->percent_sign;
	return (1);
}

int	ft_readformat(int fd, int *n, char *format, va_list ap)
{
	t_fmt	chain;

	ft_bzero(&chain, sizeof(chain));
	chain.fd = fd;
	chain.n = n;
	if (!*format)
		return (0);
	if ((chain.percent_sign = ft_strchr(format, '%')))
	{
		if ((ft_save_before_ptr(&chain, &format)) == -1)
			return (-1);
		if (ft_save_after_ptr(&chain, &format, ap) == -1)
			return (-1);
		return (ft_readformat(chain.fd, n, format, ap));
	}
	chain.str = format;
	chain.len = ft_strlen(format);
	ft_printstr(chain.fd, format, chain.len, n);
	return (1);
}
