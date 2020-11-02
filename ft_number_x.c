/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:09:47 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 06:46:21 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handling # flag
*/

int		ft_fmt_sharp_x(t_fmt *chain)
{
	void *newstr;

	if (((chain->str[0] == '0' ||\
	chain->shrp == 0) && chain->modi != 'p'))
		return (1);
	if (!(newstr = ft_strjoin("0X", chain->str)))
		exit (0);
	free(chain->str);
	chain->str = newstr;
	chain->len += 2;
	return (1);
}

/*
** Handling lowcase x
*/

void	ft_fmt_lowc(t_fmt *chain)
{
	size_t i;

	i = 0;
	while (i < chain->len)
	{
		if (chain->str[i] >= 'A' &&\
		chain->str[i] <= 'X')
			chain->str[i] = chain->str[i] + 32;
		i++;
	}
}

/*
** Format string for 'x' 'X' specs
*/

int		ft_number_x(t_fmt *chain, va_list ap)
{
	unsigned long long int	d;

	chain->modi == 'p' ? d = va_arg(ap, long int) : ft_get_size_u(chain->arg_size, &d, ap);
	if (!(chain->str = ft_itoa_base_u(d, 16)))
	{
		exit (0);
	}
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_sharp_x(chain)) ||
		!(ft_fmt_prec(chain)) ||
		!(ft_fmt_width(chain)))
	{
		return (0);
	}
	chain->x == 'x' || chain->modi == 'p' ? ft_fmt_lowc(chain) : chain->str;
	return (1);
}
