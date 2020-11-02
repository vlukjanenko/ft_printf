/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:18:44 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 03:09:18 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Set width  from format in w and return presence of it in format
*/

int	ft_width(t_fmt *chain, size_t *w)
{
	int present;

	present = chain->widt[0];
	if (present)
		*w = chain->widt[1];
	return (present);
}
