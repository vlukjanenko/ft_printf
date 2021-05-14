/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:02:55 by majosue           #+#    #+#             */
/*   Updated: 2021/05/13 22:39:25 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Preformat output for char string
** char or %
*/

int	ft_fmt_char(t_fmt *chain)
{
	void	*newstr;

	if (chain->widt[0] == 0 || chain->widt[1] <= chain->len)
		return (1);
	newstr = ft_strnew(chain->widt[1]);
	if (!(newstr))
		ft_exit();
	chain->str_need_free = 1;
	if (chain->flag[MINUS])
		ft_add_right(chain, &newstr, chain->widt[1], ' ');
	else if (chain->flag[ZERO])
		ft_add_left(chain, &newstr, chain->widt[1], '0');
	else
		ft_add_left(chain, &newstr, chain->widt[1], ' ');
	chain->str = newstr;
	chain->len = chain->widt[1];
	return (1);
}

int	ft_string(t_fmt *chain, va_list ap)
{
	chain->str = (va_arg(ap, char *));
	if (!(chain->str))
		chain->str = "(null)";
	chain->len = ft_strlen(chain->str);
	if (chain->prec[0] && chain->prec[1] <= chain->len)
		chain->len = chain->prec[1];
	if (ft_fmt_char(chain))
	{
		return (1);
	}
	return (0);
}

int	ft_char(t_fmt *chain, va_list ap)
{
	int		s1;

	if (g_modi_tab[chain->modi] == '%')
		s1 = '%';
	else
		s1 = va_arg(ap, int);
	chain->str = ft_strnew(1);
	if (!(chain->str))
		ft_exit();
	chain->str_need_free = 1;
	chain->str[0] = (char)s1;
	chain->len = 1;
	if (!(ft_fmt_char(chain)))
	{
		return (0);
	}
	return (1);
}

/*
** Handling # flag with float mod
*/

int	ft_fmt_sharp_f(t_fmt *chain)
{
	void	*newstr;

	if (!chain->flag[SHARP] || ft_strchr(chain->str, '.'))
		return (1);
	newstr = ft_strjoin(chain->str, ".");
	if (!(newstr))
		ft_exit();
	chain->str_need_free = 1;
	free(chain->str);
	chain->str = newstr;
	chain->len += 1;
	return (1);
}

/*
** Format string for f spec
*/

int	ft_float(t_fmt *chain, va_list ap)
{
	long double	d;

	if (!chain->prec[0])
	{
		chain->prec[0] = 1;
		chain->prec[1] = 6;
	}
	if (ft_strequ(chain->arg_size, "L"))
		d = va_arg(ap, long double);
	else
		d = va_arg(ap, double);
	chain->str = ft_ftoa(d, chain->prec[1]);
	if (chain->str)
		chain->len = ft_strlen(chain->str);
	else
		chain->len = 1;
	if (!chain->str || \
		!(ft_fmt_sharp_f(chain)) || \
		!(ft_fmt_plus(chain)) || \
		!(ft_fmt_width(chain)))
	{
		return (0);
	}
	chain->str_need_free = 1;
	return (1);
}
