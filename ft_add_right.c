/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:42:52 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 00:12:22 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Fill newstr with content at left & c at right
*/

void	ft_add_right(t_fmt *chain, void **newstr, size_t w, char c)
{
	void *begin;

	begin = *newstr;
	ft_memcpy(*newstr, chain->str, chain->len);
	*newstr += chain->len;
	ft_memset(*newstr, c, w - chain->len);
	*newstr = begin;
}
