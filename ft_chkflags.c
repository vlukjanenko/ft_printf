/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chkflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:02:01 by majosue           #+#    #+#             */
/*   Updated: 2020/11/02 22:38:31 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* int	ft_compare(char *flags, char c)
{
	while (*flags)
	{
		if (*flags == c)
			return (1);
		flags++;
	}
	return (0);
} */

/* int	ft_chklen(char *ptr1, char *ptr2)
{
	int n;

	n = ptr2 - ptr1;
	if (n == 0 || n == 1)
		return (1);
	if ((n == 2 && ptr1[0] == 'h' && ptr1[1] == 'h'))
		return (2);
	if ((n == 2 && ptr1[0] == 'l' && ptr1[1] == 'l'))
		return (2);
	return (0);
}
 */
/* int	ft_chkdoubledot(char *ptr1, char *ptr2)
{
	int n;

	n = 0;
	while (ptr1 != ptr2)
	{
		if (*ptr1 == '.')
		{
			n++;
		}
		ptr1++;
	}
	if (n > 1)
		return (0);
	if (n == 0)
		return (-1);
	return (1);
} */

int char_is_in_flags(char c, t_fmt *chain)
{
	if (c == '0')
		chain->zero = 1;
	else if (c == '#')
		chain->shrp = 1;
	else if (c == ' ')
		chain->spce = 1;
	else if (c == '-')
		chain->mins = 1;
	else if (c == '+')
		chain->plus = 1;
	else
		return (0);
	return (1);
}

void ft_set_w(char **str, t_fmt *chain, va_list(ap))
{
	int tmp;

	if (*(*str) == '*')
		{
			chain->widt[0] = 1;
			tmp = va_arg(ap, int);
			if (tmp < 0)
			{
				chain->widt[1] = -tmp;
				chain->mins = 1;
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

void ft_set_p(char **str, t_fmt *chain, va_list(ap))
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
		chain->arg_size = ft_strdup("hh");
		(*str) += 2;
	}
	else if (ft_strnequ(*str, "ll", 2))
	{
		chain->arg_size = ft_strdup("l");
		(*str) += 2;
	}
	else if (ft_strnequ(*str, "l", 1))
	{
		chain->arg_size = ft_strdup("l");
		(*str) += 1;
	}
	else if (ft_strnequ(*str, "h", 1))
	{
		chain->arg_size = ft_strdup("h");
		(*str) += 1;
	}
	else if (ft_strnequ(*str, "L", 1))
	{
		chain->arg_size = ft_strdup("L");
		(*str) += 1;
	}
}

int		ft_set_mod(char **str, t_fmt *chain)
{
	if (*(*str) == 'd')
		chain->modi = 'd';
	else if (*(*str) == 'i')
		chain->modi = 'i';
	else if (*(*str) == 'o')
		chain->modi = 'o';
	else if (*(*str) == 'u')
		chain->modi = 'u';
	else if (*(*str) == 'x')
	{
		chain->modi = 'X';
		chain->x = 'x';
	}
	else if (*(*str) == 'X')
		chain->modi = 'X';
	else if (*(*str) == '%')
		chain->modi = '%';
	else if (*(*str) == 'c')
		chain->modi = 'c';
	else if (*(*str) == 'p')
		chain->modi = 'p';
	else if (*(*str) == 's')
		chain->modi = 's';
	else if (*(*str) == 'f')
		chain->modi = 'f';
	else
		return (0);
	(*str)++;
	return (1);
}

int	ft_chkflags(char **str, t_fmt *chain, va_list ap)
{
	while (char_is_in_flags(*(*str), chain))
		(*str)++;
	while (*(*str) == '*' || ft_isdigit(*(*str)))
		ft_set_w(str, chain, ap);
	if (*(*str) == '.')
	{
		(*str)++;
		ft_set_p(str, chain, ap);
	}
	ft_set_arg_size(str, chain);
	return (ft_set_mod(str, chain));
}
