/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:03:21 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 03:37:44 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Put in 'd' argument appropriate unsigned size
*/

void	ft_get_size_u_part2(char *str, unsigned long long int *d, va_list ap)
{
	t_type_u tmp;

	if (ft_strequ(str, "h"))
	{
		tmp.si = va_arg(ap, unsigned int);
		*d = tmp.si;
	}
	if (ft_strequ(str, "l"))
	{
		tmp.li = va_arg(ap, unsigned long int);
		*d = tmp.li;
	}

}

void	ft_get_size_u(char *str, unsigned long long int *d, va_list ap)
{

	t_type_u	tmp;

	if (!str)
	{
		tmp.i = va_arg(ap, unsigned int);
		*d = tmp.i;
	}
	else if (ft_strequ(str, "ll"))
	{
		tmp.lli = va_arg(ap, unsigned long long int);
		*d = tmp.lli;
	}
	else if (ft_strequ(str,"hh"))
	{
		tmp.c = va_arg(ap, unsigned int);
		*d = tmp.c;
	}
	ft_get_size_u_part2(str, d, ap);
}
