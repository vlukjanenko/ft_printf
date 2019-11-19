/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readformat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:10:10 by majosue           #+#    #+#             */
/*   Updated: 2019/11/19 12:14:43 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_compare(char *flags, char c)
{
	while (*flags)
	{
		if (*flags == c)
			return (1);
		flags++;
	}
	return (0);
}

int		ft_chkflags(char **str)
{
	char fs[6];
	char mw[11];
	char pc[12];
	char lm[4];
	char cs[9];

	ft_strcpy(fs, " #0-+");
	ft_strcpy(mw, "0123456789");
	ft_strcpy(pc, ".0123456789");
	ft_strcpy(lm, "hlL");
	ft_strcpy(cs, "dinouxX%");
	while (*(*str) && ft_compare(fs, *(*str)))
		(*str)++;
	while (*(*str) && ft_compare(mw, *(*str)))
		(*str)++;
	while (*(*str) && ft_compare(pc, *(*str)))
		(*str)++;
	while (*(*str) && ft_compare(lm, *(*str)))
		(*str)++;
	if (ft_compare(cs, *(*str)))
	{
		(*str)++;
		return (1);
	}
	return (0);
}

int		ft_save_before_ptr(t_list **str, char **ptr, char **format)
{
	if (*ptr == *format)
		return (0);
	if (!(ft_lstp2back(str, *format, *ptr - *format)))
		return (-1);
	*format = *ptr;
	return (1);
}

int		ft_save_after_ptr(t_list **str, char **ptr, char **format)
{
	(*ptr)++;
	if (!ft_chkflags(ptr))
	{
		*format = *ptr;
		return (-1);
	}
	if (!(ft_lstp2back(str, *format, *ptr - *format)))
		return (-1);
	*format = *ptr;
	return (1);
}

int		ft_readformat(t_list **str, char *format)
{
	char *ptr;

	if (!*format)
		return (0);
	if ((ptr = ft_strchr(format, '%')))
	{
		if ((ft_save_before_ptr(str, &ptr, &format)) == -1)
			return (-1);
		if (ft_save_after_ptr(str, &ptr, &format) == -1)
			return (-1);
		return (ft_readformat(str, format));
	}
	if (!(ft_lstp2back(str, format, ft_strlen(format))))
		return (-1);
	return (1);
}
