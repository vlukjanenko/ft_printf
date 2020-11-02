/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:18:11 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 04:02:15 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Format string for 'u' specs
*/

#include "ft_printf.h"

int	ft_number_u(t_fmt *chain, va_list ap)
{
	unsigned long long int	d;

	ft_get_size_u(chain->arg_size, &d, ap);
	if (!(chain->str = ft_itoa_base_u(d, 10)))
	{
		return (0);
	}
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_prec(chain)) ||
		!(ft_fmt_width(chain)))
	{
		return (0);
	}
	return (1);
}
