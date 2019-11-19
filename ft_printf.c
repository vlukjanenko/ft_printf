/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/19 12:00:48 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

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

void	ft_printstr(t_list **str)
{
	int i;

	i = 0;
	while (*str)
	{
		while (i < (*str)->content_size)
		{
			ft_putchar(((char *)(*str)->content)[i]);
			i++;
		}
		i = 0;
		*str = (*str)->next;
	}
}

int		ft_save_before_ptr(t_list **str, char **ptr, char **format) // учти что сохраняется без терминатора
{
	if (*ptr == *format) //если строка начинается с процентов ничего не сохраняем
		return (0);
	if (!(ft_lstp2back(str, *format, *ptr - *format)))
		return (-1);
	*format = *ptr; // тут передвинули указатель на проценты и вернулись
	return (1);
}

int		ft_save_after_ptr(t_list **str, char **ptr, char **format)
{
	(*ptr)++;
	if (!ft_chkflags(ptr)) // ставит указатель на последний символ строки формата
	{
		*format = *ptr; // это тут не нужно н
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

int		ft_printf(const char *restrict format, ...)
{
	t_list *str;

	str = 0;
	if (!ft_readformat(&str, (char *)format))
		return (0);
	ft_printstr(&str);
	return (100);
}

int		main()
{
	char tmp;

	tmp = 126;
	//  ft_endc();
	ft_printf("Solid string % 0+-10.15d without persent");

	//printf("Проверка работы параметров%------R----------------25.25hhd\n", tmp);

	return (0);
}
