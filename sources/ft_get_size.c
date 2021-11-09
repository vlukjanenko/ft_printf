/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:26:13 by majosue           #+#    #+#             */
/*   Updated: 2021/05/13 21:54:45 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Put in 'd' argument appropriate signed size
*/

void	ft_get_size_part2(char *str, long long int *d, va_list ap)
{
	t_type	tmp;

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

	if (!str[0])
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

/*
** Put in 'd' argument appropriate unsigned size
*/

void	ft_get_size_u_part2(char *str, unsigned long long int *d, va_list ap)
{
	t_type_u	tmp;

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

	if (!str[0])
	{
		tmp.i = va_arg(ap, unsigned int);
		*d = tmp.i;
	}
	else if (ft_strequ(str, "ll"))
	{
		tmp.lli = va_arg(ap, unsigned long long int);
		*d = tmp.lli;
	}
	else if (ft_strequ(str, "hh"))
	{
		tmp.c = va_arg(ap, unsigned int);
		*d = tmp.c;
	}
	ft_get_size_u_part2(str, d, ap);
}

/*
** Return function pointer
*/

t_fun	ft_get_f(int idx)
{
	t_fun	ftab[11];

	ftab[0] = &ft_char;
	ftab[1] = &ft_string;
	ftab[2] = &ft_number_x;
	ftab[3] = &ft_number;
	ftab[4] = &ft_number;
	ftab[5] = &ft_number_o;
	ftab[6] = &ft_number_u;
	ftab[7] = &ft_number_x;
	ftab[8] = &ft_number_x;
	ftab[9] = &ft_float;
	ftab[10] = &ft_char;
	return (ftab[idx]);
}
