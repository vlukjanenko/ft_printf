/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/22 16:12:05 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int ft_string(t_list **str, int n, va_list ap)
{
	int i;
	char *s;

	i = 0;
	while (i++ < n)
		va_arg(ap, char *);
	s = va_arg(ap, char *);
	free((*str)->content);
	if (!((*str)->content = ft_strdup(s)))
		return (0);
	(*str)->content_size = ft_strlen(s);
	return (1);
}

int ft_number(t_list **str, int n, va_list ap)
{
	int i;
	int d;
	char *s;

	i = 0;
	while (i++ < n)
		va_arg(ap, char *);
	d = va_arg(ap, int);
	s = ft_itoa(d);
	free((*str)->content);
	if (!((*str)->content = ft_strdup(s)))
		return (0);
	(*str)->content_size = ft_strlen(s);
	return (1);
}
void ft_cleanup(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	ft_memdel(&content);
}

int ft_printstr(t_list *str)
{
	size_t i;
	int n;

	if (!str)
		return (0);
	i = 0;
	n = 0;
	while (str)
	{
		while (i < str->content_size)
		{
			ft_putchar(((char *)str->content)[i]);
			i++;
			n++;
		}
		i = 0;
		str = str->next;
	}
	return (n);
}
int ft_format(t_list **str, t_list *begin, va_list ap)
{
	int i;
	char tmp;
	va_list sp;
	t_fun f;

	i = 0;
	begin = *str;
	while (begin)
	{
		if (((char *)begin->content)[0] == '%')
		{
			va_copy(sp, ap);
			tmp = ((char *)begin->content)[begin->content_size - 1];
			f = ft_get_f(tmp);
			f(&begin, i, sp);
			va_end(sp);
			i++;
		}
		begin = begin->next;
	}
	return (1);
}
int ft_printf(const char *restrict format, ...)
{
	t_list *str;
	va_list ap;
	void (*del)(void *, size_t);

	del = &ft_cleanup;
	str = 0;
	if (ft_readformat(&str, (char *)format) == -1) //получили спискок строк вида строка строка формат строка и т.д.
	{
		ft_lstdel(&str, del);
		return (0);
	}
	va_start(ap, format);
	ft_format(&str, 0, ap);
	va_end(ap);
	ft_printstr(str);
	ft_lstdel(&str, del);
	return (100);
}

int main()
{
	char tmp;

	tmp = 126;
	ft_printf("well worked %09.8d - %s", 140, "ABSOLUTE\n", 350);
	return (0);
}
