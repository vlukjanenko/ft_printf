/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:26:13 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 01:35:26 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Put in 'd' argument appropriate signed size
*/

void	ft_get_size_part2(char *str, long long int *d, va_list ap)
{
	t_type tmp;

	if (ft_strequ(str, "h"))
	{
		tmp.si = va_arg(ap, int);
		*d = tmp.si;
	}
	else if (ft_strequ(str, "l"))
	{
		tmp.li = va_arg(ap, long int);
		*d = tmp.li;
	}
}

void	ft_get_size(char *str, long long int *d, va_list ap)
{
	t_type	tmp;

	if (!str)
	{
			tmp.i = va_arg(ap, int);
			*d = tmp.i;
	}
	else if (ft_strequ(str, "ll"))
	{
		tmp.lli = va_arg(ap, long long int);
		*d = tmp.lli;
	}
	else if (ft_strequ(str, "hh"))
	{
		tmp.c = va_arg(ap, int);
		*d = tmp.c;
	}
	ft_get_size_part2(str, d, ap);
}
