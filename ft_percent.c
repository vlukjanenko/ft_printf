/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 12:56:00 by majosue           #+#    #+#             */
/*   Updated: 2019/12/16 20:09:53 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_percent(t_list **str, va_list ap)
{
	char *s;

	if (!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	if (!((*str)->content = ft_strdup("%")))
	{
		free(s);
		return (0);
	}
	(*str)->content_size = 1;
	if (!(ft_fmt_char(str, s)))
	{
		free(s);
		return (0);
	}
	free(s);
	return (1);
}
