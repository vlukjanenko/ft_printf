/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:52:00 by majosue           #+#    #+#             */
/*   Updated: 2022/11/01 20:25:31 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fmt_plus(t_fmt *chain)
{
	size_t	w;
	void	*newstr;
	char	c;

	if ((chain->flag[PLUS] || chain->flag[SPACE]) && ft_isdigit(chain->str[0]))
	{
		w = chain->len + 1;
		if (w < chain->len)
			return (0);
		newstr = ft_strnew(w);
		if (!(newstr))
			return (clean_error_return (chain, 0));
		chain->str_need_free = 1;
		if (chain->flag[PLUS])
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

/*
** Format digital string without leading signs (- + or space) and without # flag
*/

int	ft_fmt_width_d(t_fmt *chain)
{
	void	*newstr;

	if (chain->widt[1] <= chain->len)
		return (1);
	newstr = ft_strnew(chain->widt[1]);
	if (!(newstr))
		return (clean_error_return (chain, 0));
	chain->str_need_free = 1;
	if (chain->flag[MINUS])
		ft_add_right(chain, &newstr, chain->widt[1], ' ');
	else if ((chain->flag[ZERO] && !chain->prec[0]) || \
			(chain->flag[ZERO] && g_modi_tab[chain->modi] == 'f'))
		ft_add_left(chain, &newstr, chain->widt[1], '0');
	else
		ft_add_left(chain, &newstr, chain->widt[1], ' ');
	free(chain->str);
	chain->str = newstr;
	chain->len = chain->widt[1];
	return (1);
}

/*
** Format digital string with leading signs (- + or space)
*/

int	ft_fmt_width_s(t_fmt *chain)
{
	char	sign;
	void	*newstr;

	sign = chain->str[0];
	if (chain->widt[1] <= chain->len)
		return (1);
	chain->str[0] = '0';
	newstr = ft_strnew(chain->widt[1]);
	if (!(newstr))
		return (clean_error_return (chain, 0));
	chain->str_need_free = 1;
	ft_add_left(chain, &newstr, chain->widt[1], '0');
	((char *)newstr)[0] = sign;
	free(chain->str);
	chain->str = newstr;
	chain->len = chain->widt[1];
	return (1);
}

/*
** Format digital string with leading 0x (# flag)
*/

int	ft_fmt_width_x(t_fmt *chain)
{
	void	*newstr;

	if (chain->widt[1] <= chain->len)
		return (1);
	chain->str[1] = '0';
	newstr = ft_strnew(chain->widt[1]);
	if (!(newstr))
		return (clean_error_return (chain, 0));
	chain->str_need_free = 1;
	ft_add_left(chain, &newstr, chain->widt[1], '0');
	((char *)newstr)[1] = 'X';
	free(chain->str);
	chain->str = newstr;
	chain->len = chain->widt[1];
	return (1);
}

/*
** Function chooser
*/

int	ft_fmt_width(t_fmt *chain)
{
	if ((!ft_isalnum(chain->str[0]) && \
		chain->flag[ZERO] == 1 && chain->prec[0] == 0 && \
		chain->flag[MINUS] == 0) || \
		(!ft_isalnum(chain->str[0]) && g_modi_tab[chain->modi] == 'f' && \
	chain->flag[ZERO] == 1 && chain->flag[MINUS] == 0))
	{
		if (!(ft_fmt_width_s(chain)))
			return (0);
	}
	else if (ft_strchr(chain->str, 'X') && \
	chain->flag[ZERO] && !chain->prec[0] && chain->flag[MINUS] == 0)
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
