/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:52:00 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 20:23:34 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Format digital string without leading signs (- + or space) and without # flag
*/

int	ft_fmt_width_d(t_fmt *chain)
{
	size_t	w;
	size_t	p;
	void	*newstr;

	p = 0;
	w = chain->len;
	ft_width(chain, &w);
	if (w <= chain->len)
		return (1);
	if (!(newstr = ft_strnew(w)))
		return (0);
	if (chain->mins)
		ft_add_right(chain, &newstr, w, ' ');
	else if ((chain->zero && !ft_prec(chain, &p)) ||\
			(chain->zero && chain->modi == 'f'))
		ft_add_left(chain, &newstr, w, '0');
	else
		ft_add_left(chain, &newstr, w, ' ');
	free(chain->str);
	chain->str = newstr;
	chain->len = w;
	return (1);
}

/*
** Format digital string with leading signs (- + or space)
*/

int	ft_fmt_width_s(t_fmt *chain)
{
	char	sign;
	size_t	p;
	size_t	size;
	void	*newstr;

	sign = chain->str[0];
	p = chain->len;
	ft_width(chain, &p);
	if (p <= chain->len)
		return (1);
	chain->str[0] = '0';
	size = p;
	if (!(newstr = ft_strnew(size)))
		return (0);
	ft_add_left(chain, &newstr, size, '0');
	((char *)newstr)[0] = sign;
	free(chain->str);
	chain->str = newstr;
	chain->len = size;
	return (1);
}

/*
** Format digital string with leading 0x (# flag)
*/

int	ft_fmt_width_x(t_fmt *chain)
{
	size_t	p;
	size_t	size;
	void	*newstr;

	p = chain->len;
	ft_width(chain, &p);
	if (p <= chain->len)
		return (1);
	chain->str[1] = '0';
	size = p;
	if (!(newstr = ft_strnew(size)))
		return (0);
	ft_add_left(chain, &newstr, size, '0');
	((char *)newstr)[1] = 'X';
	free(chain->str);
	chain->str = newstr;
	chain->len = size;
	return (1);
}

/*
** Function chooser
*/

int	ft_fmt_width(t_fmt *chain)
{
	size_t p;

	p = 0;
	if ((!ft_isalnum(chain->str[0]) &&\
	chain->zero == 1 && ft_prec(chain, &p) == 0 && chain->mins == 0) ||\
	(!ft_isalnum(chain->str[0]) && chain->modi == 'f' &&\
	chain->zero == 1 && chain->mins == 0))
	{
		if (!(ft_fmt_width_s(chain)))
			return (0);
	}
	else if (ft_strchr(chain->str, 'X') &&\
	chain->zero && !ft_prec(chain, &p) && chain->mins == 0)
	{
		if (!(ft_fmt_width_x(chain)))
			return (0);
	}
	else
	{
		if (!(ft_fmt_width_d(chain)))
			return (0);
	}
	return (1);
}
