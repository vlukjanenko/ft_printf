/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_prec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:37:59 by majosue           #+#    #+#             */
/*   Updated: 2020/11/03 05:06:41 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Set precision in p and return 1 if it exist
*/

int	ft_prec(t_fmt *chain, size_t *p)
{
	int present;

	present = chain->prec[0];
	if (present)
		*p = chain->prec[1];
	return (present);
}

int	ft_fmt_prec_x(t_fmt *chain)
{
	size_t	p;
	size_t	size;
	void	*newstr;
	int		presist;

	p = chain->len - 2;
	presist = ft_prec(chain, &p);
	if (presist && !p && chain->str[2] == '0')
	{
		chain->len--;
		return (1);
	}
	if (p <= chain->len - 2)
		return (1);
	chain->str[1] = '0';
	size = p + 2;
	if (!(newstr = ft_strnew(size)))
		ft_exit();
	chain->str_need_free = 1;
	ft_add_left(chain, &newstr, size, '0');
	((char *)newstr)[1] = 'X';
	free(chain->str);
	chain->str = newstr;
	chain->len = size;
	return (1);
}

/*
** Format presision string with leading symbols + - space
*/

int	ft_fmt_prec_s(t_fmt *chain)
{
	char	sign;
	size_t	p;
	size_t	size;
	void	*newstr;

	sign = chain->str[0];
	p = chain->len - 1;
	if (ft_prec(chain, &p) && !p && chain->str[1] == '0')
	{
		chain->len--;
		return (1);
	}
	if (p <= chain->len - 1)
		return (1);
	chain->str[0] = '0';
	size = p + 1;
	if (!(newstr = ft_strnew(size)))
		ft_exit();
	chain->str_need_free = 1;
	ft_add_left(chain, &newstr, size, '0');
	((char *)newstr)[0] = sign;
	free(chain->str);
	chain->str = newstr;
	chain->len = size;
	return (1);
}

/*
** Format precision in digital string without leading signs (- + or space)
*/

int	ft_fmt_prec_d(t_fmt *chain)
{
	size_t	p;
	int		presist;
	void	*newstr;

	p = chain->len;
	presist = ft_prec(chain, &p);
	if (presist && !p && chain->str[0] == '0')
	{
		chain->len = chain->flag[SHARP] && g_modi_tab[chain->modi] == 'o' ?
												chain->len : chain->len - 1;
		return (1);
	}
	if (p <= chain->len)
		return (1);
	if (!(newstr = ft_strnew(p)))
		ft_exit();
	chain->str_need_free = 1;
	ft_add_left(chain, &newstr, p, '0');
	free(chain->str);
	chain->str = newstr;
	chain->len = p;
	return (1);
}

/*
** Function chooser
*/

int	ft_fmt_prec(t_fmt *chain)
{
	if (ft_isalnum(chain->str[0]) &&
		!ft_strchr(chain->str, 'X'))
	{
		if (!(ft_fmt_prec_d(chain)))
			return (0);
	}
	else if (ft_strchr(chain->str, 'X'))
	{
		if (!(ft_fmt_prec_x(chain)))
			return (0);
	}
	else
	{
		if (!(ft_fmt_prec_s(chain)))
			return (0);
	}
	return (1);
}
