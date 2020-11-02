/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:48:12 by majosue           #+#    #+#             */
/*   Updated: 2020/11/01 23:15:07 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char(t_fmt *chain, va_list ap)
{
	int		s1;

	s1 = chain->modi == '%' ? '%' : (va_arg(ap, int));
	if (!(chain->str = ft_strnew(1)))
		exit (0);
	chain->str[0] = (char)s1;
	chain->len = 1;
	if (!(ft_fmt_char(chain)))
	{
		return (0);
	}
	return (1);
}
