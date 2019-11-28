/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/28 21:12:54 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

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

int ft_plus (char *str)
{
	if (ft_strchr(str, '+'))
		return (1);
	return (0);
}

int ft_skipflags(char **str)
{
	char *flags[5];
	char *str1;

	str1 = *str;
	ft_gettab(&flags, 0);
	ft_chkflags(str, flags);
	if (str1 == *str)
		return (0);
	return (1);
}
/* Get width */
int ft_width(char *str, size_t *w)
{
	int present;
	present = 0;
	
	ft_skipflags(&str);
	if (ft_isdigit(*str))
		{
			present = 1;
			*w = ft_atoi(str);
		}
	return (present);
}
/* Get precision */
int ft_prec(char *str, size_t *p)
{
	char *point;
//	size_t p1;
	int present;

	present = 0;
	//p1 = *p;
	if ((point = ft_strchr(str, '.')))
		{
			present =  1;
			*p = ft_atoi(point + 1);
		}
	//if (*p > p1)
	//	*p = p1;
	return (present);
}

/* Preformat output */
int ft_format_output(t_list **str, char *s)
{
	size_t w;
	void *newstr;
 	
	w = (*str)->content_size;
	ft_width(s, &w);
	if (w <= (*str)->content_size)
		return (1);
	if (!(newstr = ft_memalloc(w)))
		return (0);
	if (ft_minus(s))
		ft_add_right(str, &newstr, w, ' ');
	else if (ft_null(s))
		ft_add_left(str, &newstr, w, '0');
	else
		ft_add_left(str, &newstr, w, ' ');
	free((*str)->content);
	(*str)->content = newstr;
	(*str)->content_size = w;
	return(1);
}

int ft_fmt_plus(t_list **str, char *s)
{
	void *newstr;
	size_t w;
	char c;

	if ((ft_plus(s) || ft_space(s)) && ft_isdigit(((char*)(*str)->content)[0]))
	{
		if ((w = (*str)->content_size + 1) < (*str)->content_size)
			return (0);
		if (!(newstr = ft_memalloc(w)))
			return (0);
		if (ft_plus(s))
			c = '+';
		else
			c = ' ';		
		ft_add_left(str, &newstr, w, c);
		free((*str)->content);
		(*str)->content = newstr;
		(*str)->content_size = w;
	}
return (1);
}
int ft_fmt_prec_d(t_list **str, char *s)
{
	size_t p;	
	void *newstr;

	p = (*str)->content_size;
	ft_prec(s, &p);	
	if (p <= (*str)->content_size)
		return (1);
	if (!(newstr = ft_memalloc(p)))
		return (0);
	ft_add_left(str, &newstr, p, '0');
	free((*str)->content);
	(*str)->content = newstr;
	(*str)->content_size = p;
	return(1);
}

int ft_fmt_prec_s(t_list **str, char *s)
{
	char sign;
	size_t p;	
	size_t size;
	void *newstr;

	sign = ((char*)(*str)->content)[0];
	p = (*str)->content_size - 1;
	ft_prec(s, &p);	
	if (p <= (*str)->content_size - 1)
		return (1);
	((char*)(*str)->content)[0] = '0';
	size = p + 1;
	if (!(newstr = ft_memalloc(size)))
		return (0);
	ft_add_left(str, &newstr, size, '0');
	((char*)newstr)[0] = sign;
	free((*str)->content);
	(*str)->content = newstr;
	(*str)->content_size = size;
	return(1);
}
int ft_fmt_prec(t_list **str, char *s)
{
	if (ft_isdigit(((char*)(*str)->content)[0]))
	{
		if (!(ft_fmt_prec_d(str, s)))
			return (0);
	}
	else
	{
		if (!(ft_fmt_prec_s(str, s)))
			return (0);	
	}
return (1);
}
/* int ft_formatoutput2(t_list **str, char *s)
{
	size_t w;
	void *newstr;
 	size_t p;
	
	p = (*str)->content_size;
	if (ft_plus && ft_isdigit((*str)->content))

	if (!(ft_prec(s, &p)))
			return (1);
	
	ft_width(s, &w);
	if (p <= (*str)->content_size)
		return (1);
	if (!(newstr = ft_memalloc(w)))
		return (0);
	if (ft_minus(s))
		ft_add_right(str, &newstr, w, ' ');
	else if (ft_null(s))
		ft_add_left(str, &newstr, w, '0');
	else
		ft_add_left(str, &newstr, w, ' ');
	free((*str)->content);
	(*str)->content = newstr;
	(*str)->content_size = w;
	return(1);
}
 */

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
	char *s;
	char *s1;
	//size_t p;
	int d;

	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	ft_shiftarg(n, ap);
	d = va_arg(ap, int);
	s1 = ft_itoa(d);
	if (!((*str)->content = ft_strdup(s1)))
		return (0);
	(*str)->content_size = ft_strlen(s1);
	if (!(ft_fmt_plus(str, s)))
		return (0);
	if (!(ft_fmt_prec(str, s)))
		return (0);
	//if (!(ft_format_output1(str, s)))
	//	return (0);
	return (1);

		
	/* int d;
	char *s;

	ft_shiftarg(n, ap);
	d = va_arg(ap, int);

	s = ft_itoa(d);
	free((*str)->content);
	if (!((*str)->content = ft_strdup(s)))
		return (0);
	(*str)->content_size = ft_strlen(s);
	if (!(ft_format_output(str, s)))
		return (0);
	return (1); */
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
			ft_putchar(((char *)str->content)[i]); //заменить на врайт посмотреть как на скорость повлияет
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
