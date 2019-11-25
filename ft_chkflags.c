/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chkflags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:02:01 by majosue           #+#    #+#             */
/*   Updated: 2019/11/19 18:53:39 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_compare(char *flags, char c)
{
	while (*flags)
	{
		if (*flags == c)
			return (1);
		flags++;
	}
	return (0);
}

int	ft_chklen(char *ptr1, char *ptr2)
{
	int n;

	n = ptr2 - ptr1;
	if (n == 0 || n == 1)
		return (1);
	if ((n == 2 && ptr1[0] == 'h' && ptr1[1] == 'h'))
		return (1);
	if ((n == 2 && ptr1[0] == 'l' && ptr1[1] == 'l'))
		return (1);
	return (0);
}

int	ft_chkdoubledot(char *ptr1, char *ptr2)
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
	return (1);
}

int	ft_chkdouble(char *ptr1, char *ptr2)
{
	int i;
	int j;
	int n;

	n = ptr2 - ptr1;
	i = 0;
	j = 1;
	while (i < n)
	{
		while (j < n)
		{
			if (ptr1[i] == ptr1[j] && i != j)
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	ft_chkflags(char **str, char *ftab[5])
{
	char *begin;

	begin = *str;
	while (*(*str) && ft_compare(ftab[0], *(*str)))
		(*str)++;
	if (!(ft_chkdouble(begin, *str)))
		return (0);
	while (*(*str) && ft_compare(ftab[1], *(*str)))
		(*str)++;
	begin = *str;
	while (*(*str) && ft_compare(ftab[2], *(*str)))
		(*str)++;
	if (!(ft_chkdoubledot(begin, *str)))
		return (0);
	begin = *str;
	while (*(*str) && ft_compare(ftab[3], *(*str)))
		(*str)++;
	if (!(ft_chklen(begin, *str)))
		return (0);
	if (ft_compare(ftab[4], *(*str)))
	{
		(*str)++;
		return (1);
	}
	return (0);
}
