/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 11:22:31 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 15:14:34 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_dnbr(unsigned int nbr)
{
	int	dnbr;

	dnbr = 0;
	while (nbr != 0)
	{
		nbr /= 10;
		dnbr++;
	}
	if (!dnbr)
		return (1);
	return (dnbr);
}

static char	*setup_string(char **str, int size)
{
	*str = ft_strnew(size);
	return (*str);
}

static unsigned int	get_number_without_sign(int n)
{
	unsigned int	nbr;

	if (n >= 0)
		nbr = n;
	else
		nbr = -n;
	return (nbr);
}

char	*ft_itoa(int n)
{
	int				sign;
	char			*str;
	int				size;
	unsigned int	nbr;

	sign = 0;
	if (n < 0)
		sign = 1;
	nbr = get_number_without_sign(n);
	size = ft_dnbr(nbr) + sign;
	if (!setup_string(&str, size))
		return (NULL);
	if (n == 0)
		*str = '0';
	if (sign == 1)
		*str = '-';
	size--;
	while (size >= sign)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
