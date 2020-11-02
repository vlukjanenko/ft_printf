/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:06:51 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 03:19:52 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fmt_plus(t_fmt *chain)
{
	size_t	w;
	void	*newstr;
	char	c;

	if ((chain->plus || chain->spce) && ft_isdigit(chain->str[0]))
	{
		if ((w = chain->len + 1) < chain->len)
			return (0);
		if (!(newstr = ft_strnew(w)))
			return (0);
		if (chain->plus)
			c = '+';
		else
			c = ' ';
		ft_add_left(chain, &newstr, w, c);
		free(chain->str);
		chain->str = newstr;
		chain->len = w;
	}
	return (1);
}
