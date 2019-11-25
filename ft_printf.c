/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/25 20:03:01 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
int ft_minus(char *str)
{
	if (ft_strchr(str, '-'))
		return (1);
	return (0);
}

int ft_width(char *str)
{
	int w;

	w = -1;
	if (ft_strchr(str, '.'))
		w = (0);
	while (*str && ft_isdigit(*str) == 0)
		str++;
	if (*str)
		{
			w = ft_atoi(str);
			return (w);
		}
	return (w);
}

int ft_pres(char *str)
{
	int p;
	char *point;

	p = -1;
	if ((point = ft_strchr(str, '.')))
		{
			 p = ft_atoi(point + 1);
			return (p);
		}
	return (p);
}
char *ft_fillstr(int f, int w, int p, char *str)
{
	char *rezult;
	int add;
	char *tmp;
	char *tmp2;

	if (p >= 0)
		rezult = ft_strsub(str, 0, p);
	else 
		rezult = ft_strdup(str);
	add = w - ft_strlen(rezult);
	if (f == 0 && add > 0)
	{
		tmp = ft_strnew(add);
		ft_memset(tmp, ' ', add);
		tmp2 = ft_strjoin(tmp, rezult);
		free(tmp);
		free(rezult);
		rezult = tmp2;	
		//if (!(rezult = ft_strdup(str)))
		//	return (0);
	}

	return (rezult);
}

void ft_cleanflags(char *(*ftab)[5])
{
	(*ftab)[0] = "";
	(*ftab)[1] = "";
	(*ftab)[2] = "";
	(*ftab)[3] = "";
	(*ftab)[4] = "";

}

int ft_sringflags(char *str)
{
	char *s;
	char *flags[5];

	ft_cleanflags(&flags);
	flags[0] = "-";
	ft_chkflags(&str, flags);
	s = str;
	flags[0] = " #0-+";
	ft_chkflags(&str, flags);
	if (s != str)
		return (0);
	ft_gettab(&flags);
	flags[3] = "";
	flags[4] = "";
	ft_chkflags(&str, flags);
	s = str;
	ft_gettab(&flags);
	flags[4] = "";
	ft_chkflags(&str, flags);
	if (s != str)
		return (0);
	return (1);
}

int ft_string(t_list **str, int n, va_list ap)
{
	int i;
	char *s;
	int f;
	int w;
	int p;

	s = (*str)->content;
	s++;
	if (!(ft_sringflags(s)))
		return (0); //флаги инвалидные// либо валидные 
	f = ft_minus(s);
	w = ft_width(s);
	p = ft_pres(s);
	i = 0;
	while (i++ < n)
		va_arg(ap, char *);
	s = va_arg(ap, char *);
	ft_fillstr(f, w, p, s);
	free((*str)->content);
	if (!((*str)->content = ft_fillstr(f, w, p, s)))
		return (0);
	(*str)->content_size = ft_strlen((*str)->content);
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
			if (!(f(&begin, i, sp)))
				return (0);
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
	if (ft_format(&str, 0, ap) == 0) //получили спискок строк вида строка строка формат строка и т.д.
	{
		ft_lstdel(&str, del);
		return (0);
	}
	va_end(ap);
	ft_printstr(str);
	ft_lstdel(&str, del);
	return (100);
}

int main()
{
	char tmp;

	tmp = 126;
	ft_printf("well worked %d - %10.1s\n", 140, "ABSOLUTE\n", 350);
	printf("well worked %d - %10.1s", 140, "ABSOLUTE\n");
	return (0);
}
