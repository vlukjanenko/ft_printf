/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:11:42 by majosue           #+#    #+#             */
/*   Updated: 2019/12/04 19:32:54 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handle + space flags
*/

int	ft_fmt_plus(t_list **str, char *s)
{
	size_t	w;
	void	*newstr;
	char	c;

	if ((ft_plus(s) || ft_space(s)) && ft_isdigit(((char *)(*str)->content)[0]))
	{
		if ((w = (*str)->content_size + 1) < (*str)->content_size)
			return (0);
		if (!(newstr = ft_memalloc(w)))
			return (0);
		if (ft_plus(s))
			c = '+';
		else
			c = ' ';
		ft_add_left(str, &newstr, w, c);
		free((*str)->content);
		(*str)->content = newstr;
		(*str)->content_size = w;
	}
	return (1);
}

/*
** Format string for 'd' or 'i' spec
*/

int			ft_number(t_list **str, int n, va_list ap)
{
	char			*s;
	long long int	d;

	if (!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	ft_shiftarg(n, ap);
	ft_get_size(s, &d, ap);
	if (!((*str)->content = ft_itoa_base(d, 10)))
	{
		free(s);
		return (0);
	}
	(*str)->content_size = ft_strlen((*str)->content);
	if (!(ft_fmt_plus(str, s)) ||\
		!(ft_fmt_prec(str, s)) ||\
		!(ft_fmt_width(str, s)))
	{
		free(s);
		return (0);
	}
	free(s);
	return (1);
}
