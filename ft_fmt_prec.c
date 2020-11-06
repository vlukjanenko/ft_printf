/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_prec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:37:59 by majosue           #+#    #+#             */
/*   Updated: 2020/11/06 03:16:57 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_fmt_prec_x(t_fmt *chain)
{
	size_t	size;
	void	*newstr;

	if (chain->prec[0] && !chain->prec[1] && chain->str[2] == '0')
	{
		chain->len--;
		return (1);
	}
	if (chain->prec[1] <= chain->len - 2)
		return (1);
	chain->str[1] = '0';
	size = chain->prec[1] + 2;
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
	size_t	size;
	void	*newstr;

	sign = chain->str[0];
	if (chain->prec[0] && !chain->prec[0] && chain->str[1] == '0')
	{
		chain->len--;
		return (1);
	}
	if (chain->prec[1] <= chain->len - 1)
		return (1);
	chain->str[0] = '0';
	size = chain->prec[1] + 1;
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
	void	*newstr;

	if (chain->prec[0] && !chain->prec[1] && chain->str[0] == '0')
	{
		chain->len = chain->flag[SHARP] && g_modi_tab[chain->modi] == 'o' ?
												chain->len : chain->len - 1;
		return (1);
	}
	if (chain->prec[1] <= chain->len)
		return (1);
	if (!(newstr = ft_strnew(chain->prec[1])))
		ft_exit();
	chain->str_need_free = 1;
	ft_add_left(chain, &newstr, chain->prec[1], '0');
	free(chain->str);
	chain->str = newstr;
	chain->len = chain->prec[1];
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
