/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:59:42 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 04:26:02 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handling # flag
*/

int	ft_fmt_sharp_o(t_fmt *chain)
{
	void *newstr;

	if (!chain->shrp || chain->str[0] == '0')
		return (1);
	if (!(newstr = ft_strjoin("0", chain->str)))
		exit (0);
	free(chain->str);
	chain->str = newstr;
	chain->len += 1;
	return (1);
}

/*
** Format string for 'o' spec
*/

int	ft_number_o(t_fmt *chain, va_list ap)
{
	unsigned long long int	d;

	ft_get_size_u(chain->arg_size, &d, ap);
	if (!(chain->str = ft_itoa_base_u(d, 8)))
	{
		return (0);
	}
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_sharp_o(chain)) ||
		!(ft_fmt_prec(chain)) ||
		!(ft_fmt_width(chain)))
	{
		return (0);
	}
	return (1);
}
