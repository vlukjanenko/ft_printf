/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:42:20 by majosue           #+#    #+#             */
/*   Updated: 2019/12/10 20:40:29 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_str_combain(char *entire, char *bufer, char *sign, int p)
{
	size_t	len;
	char	*res;

	len = ft_strlen(sign) + ft_strlen(entire) + p;
	len = p > 0 ? len + 1 : len;
	if (!(res = ft_strnew(len)))
		return (0);
	ft_strcat(res, sign);
	ft_strcat(res, entire);
	if (p > 0)
	{
		ft_strcat(res, ".");
		ft_strcat(res, bufer);
		ft_memset(res + len - (p - ft_strlen(bufer)),\
		'0', p - ft_strlen(bufer));
	}
	return (res);
}

void	ft_to_string(char (*bufer)[60], int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		(*bufer)[i] = (*bufer)[i] + '0';
		i++;
	}
}

int		ft_round(char (*bufer)[60], int p)
{
	int hd;

	hd = (*bufer)[p] <= 5 ? 0 : 1;
	(*bufer)[p] = 0;
	while (hd == 1 && p > 0)
	{
		hd = ((*bufer)[p - 1] + 1) / 10;
		(*bufer)[p - 1] = ((*bufer)[p - 1] + 1) % 10;
		p--;
	}
	return (hd);
}

int		ft_fract(char (*bufer)[60], long double n, int p)
{
	int		i;
	int		hd;

	hd = 0;
	i = 0;
	while (n > 0)
	{
		n = n * 10;
		(*bufer)[i] = (int)n;
		n = n - (int)n;
		i++;
	}
	if (i > p)
	{
		hd = ft_round(bufer, p);
		ft_to_string(bufer, p);
	}
	else
		ft_to_string(bufer, i);
	return (hd);
}

char	*ft_ftoa(long double n, int p)
{
	char	*sign;
	char	*entire;
	char	*rezult;
	char	bufer[60];
	int		hd;

	sign = n < 0 ? "-" : "";
	n = n < 0 ? -n : n;
	ft_bzero(bufer, 60);
	hd = ft_fract(&bufer, n - (long int)n, p);
	entire = ft_itoa_base((long int)n + hd, 10);
	if (!(rezult = ft_str_combain(entire, bufer, sign, p)))
		return (0);
	return (rezult);
}
