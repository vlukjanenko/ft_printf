/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:09:47 by majosue           #+#    #+#             */
/*   Updated: 2020/11/03 05:11:46 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Set width  from format in w and return presence of it in format
*/

int		ft_width(t_fmt *chain, size_t *w)
{
	int present;

	present = chain->widt[0];
	if (present)
		*w = chain->widt[1];
	return (present);
}

/*
** Handling # flag
*/

int		ft_fmt_sharp_x(t_fmt *chain)
{
	void *newstr;

	if (((chain->str[0] == '0' ||\
	chain->flag[SHARP] == 0) && g_modi_tab[chain->modi] != 'p'))
		return (1);
	if (!(newstr = ft_strjoin("0X", chain->str)))
		ft_exit();
	chain->str_need_free = 1;
	free(chain->str);
	chain->str = newstr;
	chain->len += 2;
	return (1);
}

/*
** Handling lowcase x
*/

void	ft_fmt_lowc(t_fmt *chain)
{
	size_t i;

	i = 0;
	while (i < chain->len)
	{
		if (chain->str[i] >= 'A' &&\
		chain->str[i] <= 'X')
			chain->str[i] = chain->str[i] + 32;
		i++;
	}
}

/*
** Format string for 'x' 'X' specs
*/

int		ft_number_x(t_fmt *chain, va_list ap)
{
	unsigned long long int	d;

	g_modi_tab[chain->modi] == 'p' ? d = va_arg(ap, long int) :
						ft_get_size_u(chain->arg_size, &d, ap);
	if (!(chain->str = ft_itoa_base_u(d, 16)))
	{
		ft_exit();
	}
	chain->str_need_free = 1;
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_sharp_x(chain)) ||
		!(ft_fmt_prec(chain)) ||
		!(ft_fmt_width(chain)))
	{
		return (0);
	}
	g_modi_tab[chain->modi] == 'x' || g_modi_tab[chain->modi] == 'p' ?
										ft_fmt_lowc(chain) : chain->str;
	return (1);
}
