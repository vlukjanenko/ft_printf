/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:53:19 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 04:21:55 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handling # flag
*/

int	ft_fmt_sharp_f(t_fmt *chain)
{
	void *newstr;

	if (!chain->shrp || ft_strchr(chain->str, '.'))
		return (1);
	if (!(newstr = ft_strjoin(chain->str, ".")))
		return (0);
	free(chain->str);
	chain->str = newstr;
	chain->len += 1;
	return (1);
}

/*
** Format string for f spec
*/

int	ft_float(t_fmt *chain, va_list ap)
{
	long double	d;
	size_t		p;

	p = 6;
	ft_prec(chain, &p);
	d = ft_strequ(chain->arg_size, "L") ? va_arg(ap, long double) : va_arg(ap, double);
	chain->str = ft_ftoa(d, p);
	chain->str ? chain->len = ft_strlen(chain->str) : 1;
	if (!chain->str ||\
		!(ft_fmt_sharp_f(chain)) ||
		!(ft_fmt_plus(chain)) ||
		!(ft_fmt_width(chain)))
	{
		return (0);
	}
	return (1);
}
