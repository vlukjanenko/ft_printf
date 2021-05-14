/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 16:25:53 by majosue           #+#    #+#             */
/*   Updated: 2021/05/14 06:56:48 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	rn(unsigned long long value, int base)
{
	int	rn;

	rn = 0;
	while (value > 0)
	{
		value = value / base;
		rn++;
	}
	if (rn == 0)
		return (1);
	return (rn);
}

/* char	*ft_itoa_base(long long int value, int base)
{
	unsigned long long int	uvalue;
	char					*rezult;
	int						rezult_size;
	int						sign;

	sign = 0;
	if (base < 2 || base > 16)
		return ((void *)0);
	if (value < 0)
	{
		uvalue = -value;
		if (base == 10)
			sign = 1;
	}
	else
		uvalue = value;
	rezult_size = rn(uvalue, base);
	rezult_size += sign;
	rezult = (char *)malloc(sizeof(char) * (rezult_size + 1));
	if (!(rezult))
		return ((void *)0);
	rezult[rezult_size] = '\0';
	if (sign)
		rezult[0] = '-';
	while ((rezult_size - 1) >= sign)
	{
		if ((uvalue % base) >= 10)
		{
			rezult[rezult_size - 1] = uvalue % base - 10 + 'A';
		}
		else
		{
			rezult[rezult_size - 1] = uvalue + '0';
		}
		uvalue /= base;
		rezult_size--;
	}
	return (rezult);
}
 */
char	*ft_itoa_base_u(unsigned long long int value, int base)
{
	char	*rezult;
	int		rezult_size;

	if (base < 2 || base > 16)
		return ((void *)0);
	rezult_size = rn(value, base);
	rezult = (char *)malloc(sizeof(char) * (rezult_size + 1));
	if (!(rezult))
		return ((void *)0);
	rezult[rezult_size] = '\0';
	while ((rezult_size - 1) >= 0)
	{
		if ((value % base) >= 10)
		{
			rezult[rezult_size - 1] = value % base - 10 + 'A';
		}
		else
		{
			rezult[rezult_size - 1] = value % base + '0';
		}
		value /= base;
		rezult_size--;
	}
	return (rezult);
}

char	*ft_itoa_base(long long int value, int base)
{
	unsigned long long int	uvalue;
	char					*subrezult;
	char					*rezult;
	char					*sign;

	sign = "";
	if (value < 0)
	{
		uvalue = -value;
		if (base == 10)
			sign = "-";
	}
	else
		uvalue = value;
	subrezult = ft_itoa_base_u(uvalue, base);
	if (!subrezult)
		return (NULL);
	rezult = ft_strjoin(sign, subrezult);
	if (!rezult)
		return (NULL);
	free(subrezult);
	return (rezult);
}
