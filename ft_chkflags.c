/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chkflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:02:01 by majosue           #+#    #+#             */
/*   Updated: 2020/11/03 05:00:18 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_char_in_tab(const char *flags, char c, int *idx)
{
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i] == c)
		{
			*idx = i;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_set_w(char **str, t_fmt *chain, va_list ap)
{
	int tmp;

	if (*(*str) == '*')
	{
		chain->widt[0] = 1;
		tmp = va_arg(ap, int);
		if (tmp < 0)
		{
			chain->widt[1] = -tmp;
			chain->flag[MINUS] = 1;
		}
		else
			chain->widt[1] = tmp;
		(*str)++;
	}
	else if (ft_isdigit(*(*str)))
	{
		chain->widt[0] = 1;
		chain->widt[1] = ft_atoi(*str);
		while (ft_isdigit(*(*str)))
			(*str)++;
	}
}

void	ft_set_p(char **str, t_fmt *chain, va_list ap)
{
	int tmp;

	chain->prec[0] = 1;
	chain->prec[1] = 0;
	if (*(*str) == '*')
	{
		chain->prec[0] = 1;
		tmp = va_arg(ap, int);
		if (tmp < 0)
			chain->prec[0] = 0;
		else
		{
			chain->prec[1] = tmp;
		}
		(*str)++;
	}
	else if (ft_isdigit(*(*str)))
	{
		chain->prec[0] = 1;
		chain->prec[1] = ft_atoi(*str);
		while (ft_isdigit(*(*str)))
			(*str)++;
	}
}

void	ft_set_arg_size(char **str, t_fmt *chain)
{
	if (ft_strnequ(*str, "hh", 2))
	{
		ft_strcpy(chain->arg_size, "hh");
		(*str) += 2;
	}
	else if (ft_strnequ(*str, "ll", 2))
	{
		ft_strcpy(chain->arg_size, "ll");
		(*str) += 2;
	}
	else if (ft_strnequ(*str, "l", 1))
	{
		ft_strcpy(chain->arg_size, "l");
		(*str) += 1;
	}
	else if (ft_strnequ(*str, "h", 1))
	{
		ft_strcpy(chain->arg_size, "h");
		(*str) += 1;
	}
	else if (ft_strnequ(*str, "L", 1))
	{
		ft_strcpy(chain->arg_size, "L");
		(*str) += 1;
	}
}

int		ft_chkflags(char **str, t_fmt *chain, va_list ap)
{
	int idx;

	while (is_char_in_tab(g_flag_tab, *(*str), &idx))
	{
		chain->flag[idx] = 1;
		(*str)++;
	}
	while (*(*str) == '*' || ft_isdigit(*(*str)))
		ft_set_w(str, chain, ap);
	if (*(*str) == '.')
	{
		(*str)++;
		ft_set_p(str, chain, ap);
	}
	ft_set_arg_size(str, chain);
	if (is_char_in_tab(g_modi_tab, *(*str), &idx))
	{
		chain->modi = idx;
		(*str)++;
		return (1);
	}
	return (0);
}
