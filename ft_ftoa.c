/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:42:20 by majosue           #+#    #+#             */
/*   Updated: 2021/05/14 06:10:38 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_str_combain(char *entire, char *bufer, char *sign, int p)
{
	size_t	len;
	char	*res;

	len = ft_strlen(sign) + ft_strlen(entire) + p;
	if (p > 0)
		len++;
	res = ft_strnew(len);
	if (!(res))
		return (0);
	ft_strcat(res, sign);
	ft_strcat(res, entire);
	if (p > 0)
	{
		ft_strcat(res, ".");
		ft_strcat(res, bufer);
		ft_memset(res + len - (p - ft_strlen(bufer)), \
		'0', p - ft_strlen(bufer));
	}
	return (res);
}

int	ft_round(char (*bufer)[70], int p)
{
	int	hd;

	if ((*bufer)[p] < 5)
		hd = 0;
	else
		hd = 1;
	(*bufer)[p] = 0;
	while (hd == 1 && p > 0)
	{
		hd = ((*bufer)[p - 1] + 1) / 10;
		(*bufer)[p - 1] = ((*bufer)[p - 1] + 1) % 10;
		p--;
	}
	return (hd);
}

int	ft_to_string(char (*bufer)[70], int p, int i)
{
	int	j;
	int	n;
	int	hd;

	hd = 0;
	if (i > p)
	{
		hd = ft_round(bufer, p);
		n = p;
	}
	else
		n = i;
	if (n > 70)
		n = 70;
	j = 0;
	while (j < n)
	{
		(*bufer)[j] = (*bufer)[j] + '0';
		j++;
	}
	return (hd);
}

int	ft_fract(char (*bufer)[70], long double n, int p)
{
	int					i;
	int					hd;
	unsigned long long	tmp;
	long double			m;

	m = n;
	hd = 0;
	i = 0;
	tmp = 10;
	while (n > 0 && i < 70)
	{
		n = 10 * n;
		if (i < 19)
			(*bufer)[i] = (unsigned long long)(m * tmp) % 10;
		else
			(*bufer)[i] = (char)(n);
		tmp *= 10;
		n = (n - (char)n);
		i++;
	}
	hd = ft_to_string(bufer, p, i);
	return (hd);
}

/*
**	Output string from long double n with precidion p
**
**	entire - integer part +
**	hd - integer result of rounding fract part
**	buffer - holde fract part;
*/

char	*ft_ftoa(long double n, int p)
{
	char	*sign;
	char	*entire;
	char	*rezult;
	char	bufer[70];
	int		hd;

	if (n < 0)
	{
		sign = "-";
		n = -n;
	}
	else
		sign = "";
	ft_bzero(bufer, 70);
	hd = ft_fract(&bufer, n - (long int)n, p);
	entire = ft_itoa_base((long int)n + hd, 10);
	if (!(entire))
		return (0);
	rezult = ft_str_combain(entire, bufer, sign, p);
	if (!(rezult))
		return (0);
	free(entire);
	return (rezult);
}
