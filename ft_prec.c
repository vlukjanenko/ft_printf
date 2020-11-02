/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:29:15 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 03:08:56 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Set precision in p and return 1 if it exist
*/

int	ft_prec(t_fmt *chain, size_t *p)
{
	int		present;

	present = chain->prec[0];
	if (present)
		*p = chain->prec[1];
	return (present);
}
