/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:51:55 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 04:23:58 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Preformat output for char string
** char or %
*/

int	ft_fmt_char(t_fmt *chain)
{
	void	*newstr;

	if (chain->widt[0] == 0 || chain->widt[1] <= chain->len)
		return (1);
	if (!(newstr = ft_strnew(chain->widt[1])))
		exit (0);
	if (chain->mins)
		ft_add_right(chain, &newstr, chain->widt[1], ' ');
	else if (chain->zero)
		ft_add_left(chain, &newstr, chain->widt[1], '0');
	else
		ft_add_left(chain, &newstr, chain->widt[1], ' ');
	//free(chain->str); //сторка изначально берется из параметров и чистить её не надо
	chain->str = newstr;
	chain->len = chain->widt[1];
	return (1);
}
