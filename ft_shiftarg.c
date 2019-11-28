/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shiftarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:59:01 by majosue           #+#    #+#             */
/*   Updated: 2019/11/28 11:00:11 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Shift to "n" agrument
*/

void	ft_shiftarg(int n, va_list ap)
{
	int i;

	i = 0;
	while (i++ < n)
		va_arg(ap, char *);
}
