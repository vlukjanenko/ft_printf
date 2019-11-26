/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readformat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:10:10 by majosue           #+#    #+#             */
/*   Updated: 2019/11/26 12:41:02 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_gettab(char *(*ftab)[5])
{
	(*ftab)[0] = " #0-+";
	(*ftab)[1] = "0123456789";
	(*ftab)[2] = ".0123456789";
	(*ftab)[3] = "hlL";
	(*ftab)[4] = "cspdiouxXf%";
}

t_fun	ft_get_f(char c)
{
	int i;
	t_fun ftab[11];
	char *s;

	s = "cspdiouxXf%";
	i = 0;
	while (s[i] && s[i] != c)
		i++;
//	ftab[0] = &ft_char;
	ftab[1] = &ft_string;
//	ftab[2] = &ft_pointer;
	ftab[3] = &ft_number;
	ftab[4] = &ft_number;
	ftab[5] = &ft_number;
	ftab[6] = &ft_number;
	ftab[7] = &ft_number;
	ftab[8] = &ft_number;
//	ftab[9] = &ft_float;
	ftab[10] = &ft_persent;
	return (ftab[i]);
}

int	ft_save_before_ptr(t_list **str, char **ptr, char **format)
{
	if (*ptr == *format)
		return (0);
	if (!(ft_lstp2back(str, *format, *ptr - *format)))
		return (-1);
	*format = *ptr;
	return (1);
}

int	ft_save_after_ptr(t_list **str, char **ptr, char **format)
{
	char *ftab[5];

	ft_gettab(&ftab);
	(*ptr)++;
	if (!ft_chkflags(ptr, ftab))
	{
		*format = *ptr;
		return (1);
	}
	if (!(ft_lstp2back(str, *format, *ptr - *format)))
		return (-1);
	*format = *ptr;
	return (1);
}

int	ft_readformat(t_list **str, char *format)
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
