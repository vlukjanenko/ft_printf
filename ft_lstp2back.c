/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstp2back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:01:24 by majosue           #+#    #+#             */
/*   Updated: 2021/05/13 21:55:37 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*ft_lstp2back(t_list **begin_list, \
void const *content, size_t content_size)
{
	t_list	*var1;

	var1 = *begin_list;
	if (var1 == 0)
	{
		return (*begin_list = ft_lstnew(content, content_size));
	}
	while (var1->next != 0)
	{
		var1 = var1->next;
	}
	var1->next = ft_lstnew(content, content_size);
	return (var1->next);
}

/*
** Fill newstr with content at right & c at left
*/

void	ft_add_left(t_fmt *chain, void **newstr, size_t w, char c)
{
	void	*begin;

	begin = *newstr;
	ft_memset(*newstr, c, w - chain->len);
	*newstr += w - chain->len;
	ft_memcpy(*newstr, chain->str, chain->len);
	*newstr = begin;
}

/*
** Fill newstr with content at left & c at right
*/

void	ft_add_right(t_fmt *chain, void **newstr, size_t w, char c)
{
	void	*begin;

	begin = *newstr;
	ft_memcpy(*newstr, chain->str, chain->len);
	*newstr += chain->len;
	ft_memset(*newstr, c, w - chain->len);
	*newstr = begin;
}
