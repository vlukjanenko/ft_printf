/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:48:12 by majosue           #+#    #+#             */
/*   Updated: 2019/11/29 12:50:17 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_char(t_list **str, int n, va_list ap)
{
	char	*s;
	int		s1;

	if (!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	ft_shiftarg(n, ap);
	free((*str)->content);
	s1 = (va_arg(ap, int));
	if (!((*str)->content = ft_strnew(1)))
		return (0);
	((char *)(*str)->content)[0] = (char)s1;
	(*str)->content_size = 1;
	if (!(ft_fmt_char(str, s)))
		return (0);
	return (1);
}