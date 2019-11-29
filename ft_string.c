/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:02:55 by majosue           #+#    #+#             */
/*   Updated: 2019/11/29 13:04:43 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_string(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	size_t p;

	if (!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	ft_shiftarg(n, ap);
	if (!(s1 = (va_arg(ap, char *))))
	{
		if (!((*str)->content = ft_strdup("(null)")))
			return (0);
		(*str)->content_size = 6;
		return (1);
	}
	p = ft_strlen(s1);
	ft_prec(s, &p);
	p = p > ft_strlen(s1) ? ft_strlen(s1) : p;
	if (!((*str)->content = ft_strsub(s1, 0, p)))
		return (0);
	(*str)->content_size = p;
	if (!(ft_fmt_char(str, s)))
		return (0);
	return (1);
}
