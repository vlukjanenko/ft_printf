/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:56:00 by majosue           #+#    #+#             */
/*   Updated: 2019/11/29 12:59:38 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_percent(t_list **str, int n, va_list ap)
{
	char *s;

	if (!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	ft_shiftarg(n, ap);
	free((*str)->content);
	if (!((*str)->content = ft_strdup("%")))
		return (0);
	(*str)->content_size = 1;
	if (!(ft_fmt_char(str, s)))
		return (0);
	return (1);
}
