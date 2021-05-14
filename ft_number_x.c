/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 19:09:47 by majosue           #+#    #+#             */
/*   Updated: 2021/05/13 22:04:24 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Handling # flag
*/

int	ft_fmt_sharp_x(t_fmt *chain)
{
	void	*newstr;

	if (((chain->str[0] == '0' || \
	chain->flag[SHARP] == 0) && g_modi_tab[chain->modi] != 'p'))
		return (1);
	newstr = ft_strjoin("0X", chain->str);
	if (!(newstr))
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
	size_t	i;

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

int	ft_number_x(t_fmt *chain, va_list ap)
{
	unsigned long long int	d;

	if (g_modi_tab[chain->modi] == 'p')
		d = va_arg(ap, long int);
	else
		ft_get_size_u(chain->arg_size, &d, ap);
	chain->str = ft_itoa_base_u(d, 16);
	if (!(chain->str))
		ft_exit();
	chain->str_need_free = 1;
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_sharp_x(chain)) || \
		!(ft_fmt_prec(chain)) || \
		!(ft_fmt_width(chain)))
		return (0);
	if (g_modi_tab[chain->modi] == 'x' || g_modi_tab[chain->modi] == 'p')
		ft_fmt_lowc(chain);
	return (1);
}
