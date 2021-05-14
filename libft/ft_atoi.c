/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 18:01:53 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 16:55:10 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	long	over;

	result = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' ||\
*str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		sign = 44 - *str;
		str++;
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		over = result;
		result = result * 10 + *str - '0';
		if (over > result && sign == -1)
			return (0);
		if (over > result && sign == 1)
			return (-1);
		str++;
	}
	return (sign * result);
}
