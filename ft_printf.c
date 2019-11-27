/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/27 15:18:31 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/* Shift to "n" agrument */
void ft_shiftarg(int n, va_list ap)
{
	int i;

	i = 0;
	while (i++ < n)
		va_arg(ap, char *);
}
/* Find '0' in flags */
int ft_null(char *str)
{
	char *flags[5];
	char *str2;
	
	str2 = str;	
	ft_gettab(&flags, 0);
	ft_chkflags(&str, flags);
	if (ft_memchr(str2, '0', str - str2))
		return (1);
	return (0);
}
/* Find ' ' in flags */
int ft_space(char *str)
{
	if (ft_strchr(str, ' '))
		return (1);
	return (0);
}
/* Find minus in flags */
int ft_minus(char *str)
{
	if (ft_strchr(str, '-'))
		return (1);
	return (0);
}

void ft_skipflags(char **str)
{
	char *flags[5];
	
	ft_gettab(&flags, 0);
	ft_chkflags(str, flags);
}
/* Get width */
void ft_width(char *str, size_t *w)
{
	ft_skipflags(&str);
	*w = ft_atoi(str);
}
/* Get precision */
void ft_prec(char *str, size_t *p)
{
	char *point;
	size_t p1;

	p1 = *p;
	if ((point = ft_strchr(str, '.')))
		{
			 p1 = ft_atoi(point + 1);
		}
	if (*p > p1)
		*p = p1;
}
/* Preformat output */
int ft_format_output(t_list **str, char *s)
{
	size_t w;
 	char *fill;
	char *tmp;
	
	w = (*str)->content_size;
	ft_width(s, &w);
	if (w <= (*str)->content_size)
		return (1);
	if(!(fill = ft_strnew(w - (*str)->content_size)))
		return (0);
	if (ft_minus(s))
	{
		ft_memset(fill, ' ', w - (*str)->content_size);
		tmp = (*str)->content;
		if (!((*str)->content = ft_strjoin((*str)->content, fill)))
			return (0);
		free(tmp);
		(*str)->content_size = w;
	}
	else if (ft_null(s))
	{
		ft_memset(fill, '0', w - (*str)->content_size);
		tmp = (*str)->content;
		if (!((*str)->content = ft_strjoin(fill, (*str)->content)))
			return (0);
		free(tmp);
		(*str)->content_size = w;
	}
	else
	{
		ft_memset(fill, ' ', w - (*str)->content_size);
		tmp = (*str)->content;
		if (!((*str)->content = ft_strjoin(fill, (*str)->content)))
			return (0);
		free(tmp);
		(*str)->content_size = w;
	}
	return (1);
}

int ft_string(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	size_t p;
	
	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	ft_shiftarg(n, ap);
	if(!(s1 = (va_arg(ap, char *))))
		{
			if (!((*str)->content = ft_strdup("(null)")))
				return (0);
			(*str)->content_size = 6;	
			return (1);
		}
	p = ft_strlen(s1);

	ft_prec(s, &p);
	if (!((*str)->content = ft_strsub(s1, 0, p)))
		return (0);
	(*str)->content_size = p;
	if (!(ft_format_output(str, s)))
		return (0);
	return (1);
}

int ft_number(t_list **str, int n, va_list ap)
{
	int d;
	char *s;

	ft_shiftarg(n, ap);
	d = va_arg(ap, int);
	s = ft_itoa(d);
	free((*str)->content);
	if (!((*str)->content = ft_strdup(s)))
		return (0);
	(*str)->content_size = ft_strlen(s);
	/* if (!(ft_format_output(str, s)))
		return (0); */
	return (1);
}
int ft_persent(t_list **str, int n, va_list ap)
{
	char *s;
	
	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	ft_shiftarg(n, ap);
	free((*str)->content);
	if (!((*str)->content = ft_strdup("%")))
		return (0);
	(*str)->content_size = 1;
	if (!(ft_format_output(str, s)))
		return (0);
	return (1);
}

int ft_char(t_list **str, int n, va_list ap)
{
	char *s;
	int s1;
 
	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	ft_shiftarg(n, ap);
	free((*str)->content);
	s1 = (va_arg(ap, int));
	if (!((*str)->content = ft_strnew(1)))
		return (0);
	((char*)(*str)->content)[0] = (char)s1;
	(*str)->content_size = 1;
	if (!(ft_format_output(str, s)))
		return (0);
	return (1);
}

void ft_cleanup(void *content, size_t content_size)
{
	if (content)
	{
		ft_bzero(content, content_size);
		ft_memdel(&content);
	}
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
	//void (*del)(void *, size_t);
	int n;

//	del = &ft_cleanup;
	str = 0;
	if (ft_readformat(&str, (char *)format) == -1) //получили спискок строк вида строка строка формат строка и т.д.
	{
	//	ft_lstdel(&str, del);
		return (0);
	}
	va_start(ap, format);
	if (ft_format(&str, 0, ap) == 0) //получили спискок строк вида строка строка формат строка и т.д.
	{
	//	ft_lstdel(&str, del);
		return (0);
	}
	va_end(ap);
	n = ft_printstr(str);
//	ft_lstdel(&str, del);
	return (n);
}
