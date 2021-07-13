/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:11:42 by majosue           #+#    #+#             */
/*   Updated: 2021/07/13 19:24:56 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Format string for 'd' or 'i' spec
*/

int	ft_number(t_fmt *chain, va_list ap)
{
	long long int	d;

	ft_get_size(chain->arg_size, &d, ap);
	chain->str = ft_itoa_base(d, 10);
	if (!(chain->str))
	{
		return (clean_error_return (chain, -1));
	}
	chain->str_need_free = 1;
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_plus(chain)) || \
		!(ft_fmt_prec(chain)) || \
		!(ft_fmt_width(chain)))
	{
		return (clean_error_return (chain, -1));
	}
	return (1);
}

/*
** Handling # flag
*/

int	ft_fmt_sharp_o(t_fmt *chain)
{
	void	*newstr;

	if (!chain->flag[SHARP] || chain->str[0] == '0')
		return (1);
	newstr = ft_strjoin("0", chain->str);
	if (!(newstr))
		return (0);
	chain->str_need_free = 1;
	free(chain->str);
	chain->str = newstr;
	chain->len += 1;
	return (1);
}

/*
** Format string for 'o' spec
*/

int	ft_number_o(t_fmt *chain, va_list ap)
{
	unsigned long long int	d;

	ft_get_size_u(chain->arg_size, &d, ap);
	chain->str = ft_itoa_base_u(d, 8);
	if (!(chain->str))
	{
		return (clean_error_return (chain, -1));
	}
	chain->str_need_free = 1;
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_sharp_o(chain)) || \
		!(ft_fmt_prec(chain)) || \
		!(ft_fmt_width(chain)))
	{
		return (clean_error_return (chain, -1));
	}
	return (1);
}

int	ft_number_u(t_fmt *chain, va_list ap)
{
	unsigned long long int	d;

	ft_get_size_u(chain->arg_size, &d, ap);
	chain->str = ft_itoa_base_u(d, 10);
	if (!(chain->str))
	{
		return (clean_error_return (chain, -1));
	}
	chain->str_need_free = 1;
	chain->len = ft_strlen(chain->str);
	if (!(ft_fmt_prec(chain)) || \
		!(ft_fmt_width(chain)))
	{
		return (clean_error_return (chain, -1));
	}
	return (1);
}
