/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 10:36:09 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 00:13:43 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Fill newstr with content at right & c at left
*/

void	ft_add_left(t_fmt *chain, void **newstr, size_t w, char c)
{
	void *begin;

	begin = *newstr;
	ft_memset(*newstr, c, w - chain->len);
	*newstr += w - chain->len;
	ft_memcpy(*newstr, chain->str, chain->len);
	*newstr = begin;
}
