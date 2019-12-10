/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:53:19 by majosue           #+#    #+#             */
/*   Updated: 2019/12/10 20:38:30 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Format string for f spec
*/

int	ft_float(t_list **str, int n, va_list ap)
{
	char		*s;
	long double	d;
	size_t		p;

	p = 6;
	if (!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	ft_shiftarg(n, ap);
	ft_prec(s, &p);
	d = ft_strchr(s, 'L') ? va_arg(ap, long double) : va_arg(ap, double);
	if (!((*str)->content = ft_ftoa(d, p)))
	{
		free(s);
		return (0);
	}
	(*str)->content_size = ft_strlen((*str)->content);
	if (!(ft_fmt_plus(str, s)) ||
		!(ft_fmt_width(str, s)))
	{
		free(s);
		return (0);
	}
	free(s);
	return (1);
}
