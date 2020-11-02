/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:11:42 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 04:25:40 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Format string for 'd' or 'i' spec
*/

int			ft_number(t_fmt *chain, va_list ap)
{
	long long int	d;

	ft_get_size(chain->arg_size, &d, ap);
	if (!(chain->str = ft_itoa_base(d, 10)))
	{
		exit (0);
	}
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_plus(chain)) ||\
		!(ft_fmt_prec(chain)) ||\
		!(ft_fmt_width(chain)))
	{
		return (0);
	}
	return (1);
}
