/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:02:55 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 01:05:40 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_string(t_fmt *chain, va_list ap)
{
	if (!(chain->str = (va_arg(ap, char *))))
		chain->str = "(null)";
	chain->len = ft_strlen(chain->str);
	chain->len = chain->prec[0] && chain->prec[1] <= chain->len ? chain->prec[1] : chain->len;

	if (ft_fmt_char(chain))
	{
		return (1);
	}
	return (0);
}
