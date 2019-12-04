/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/12/04 10:02:51 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int ft_sharp(char *s)
{
	if (ft_strchr(s, '#'))
		return (1);
	return (0);
}

int	ft_fmt_sharp(t_list **str, char *s)
{
	size_t	w;
	void	*newstr;
	char	c;

	if ((ft_sharp(s) || ft_space(s)) && ft_isdigit(((char *)(*str)->content)[0]))
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

int ft_fmt_width_d(t_list **str, char *s)
{
	size_t w;
	size_t p;
	void *newstr;
 	
	p = 0; 
	w = (*str)->content_size;
	ft_width(s, &w);
	if (w <= (*str)->content_size)
		return (1);
	if (!(newstr = ft_memalloc(w)))
		return (0);
	if (ft_minus(s))
		ft_add_right(str, &newstr, w, ' ');
	else if (ft_null(s) && !ft_prec(s, &p))
		ft_add_left(str, &newstr, w, '0');
	else
		ft_add_left(str, &newstr, w, ' ');
	free((*str)->content);
	(*str)->content = newstr;
	(*str)->content_size = w;
	return(1);
}
void ft_fmt_lowc(t_list **str)
{
	size_t i;

	i = 0;
	while (i < (*str)->content_size)
	{
		if (((char*)(*str)->content)[i] >= 'A' && ((char*)(*str)->content)[i] <= 'X')
			((char*)(*str)->content)[i] = ((char*)(*str)->content)[i] + 32;
		i++;
	}
}

int ft_fmt_prec_d(t_list **str, char *s)
{
	size_t p;	
	int presist;
	void *newstr;
	
	p = (*str)->content_size;
	presist = ft_prec(s, &p);	
	if (presist && !p && ((char*)(*str)->content)[0] == '0')
	{
		(*str)->content_size = 0;
		return (1);
	}
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
int ft_fmt_width_s(t_list **str, char *s)
{
	char sign;
	size_t p;	
	size_t size;
	void *newstr;

	sign = ((char*)(*str)->content)[0];
	p = (*str)->content_size;
	ft_width(s, &p);	
	if (p <= (*str)->content_size)
		return (1);
	((char*)(*str)->content)[0] = '0';
	size = p;
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

int ft_fmt_width(t_list **str, char *s)
{
	size_t p;

	p = 0;
	if (!ft_isdigit(((char*)(*str)->content)[0]) && ft_null(s) && !ft_prec(s, &p) && !ft_minus(s))
	{
		if (!(ft_fmt_width_s(str, s)))
			return (0);
	}
	else
	{
		if (!(ft_fmt_width_d(str, s)))
			return (0);	
	}
return (1);
}

void ft_get_size_part2(char *str, long long int *d, va_list ap)
{
	t_type tmp;

	if (str[0] == 'h' && str[1] != 'h')
		{
			tmp.si = va_arg(ap, int);
			*d = tmp.si;
		}
	if (str[0] == 'l' && str[1] != 'l')
		{
			tmp.li = va_arg(ap, long int);
			*d = tmp.li;
		}
	if (str[0] != 'l' && str[0] != 'h' && str[0] != 'L')
		{
			tmp.i = va_arg(ap, int);
			*d = tmp.i;
		}
}
void ft_get_size(char *str, long long int *d, va_list ap)
{
	char *s[5];
	
	ft_gettab(&s, 5);
	t_type tmp;

	s[3] = "";
	s[4] = "";
	ft_chkflags(&str, s);
	if (str[0] == 'l' && str [1] == 'l')
		{
			tmp.lli = va_arg(ap, long long int);
			*d = tmp.lli;
		}
	if (str[0] == 'h' && str [1] == 'h')
		{
			tmp.c =  va_arg(ap, int);
			*d = tmp.c;
		}
	ft_get_size_part2(str, d, ap);
}
//------------
void ft_get_size_u_part2(char *str, unsigned long long int *d, va_list ap)
{
	t_type_u tmp;

	if (str[0] == 'h' && str[1] != 'h')
		{
			tmp.si = va_arg(ap, int);
			*d = tmp.si;
		}
	if (str[0] == 'l' && str[1] != 'l')
		{
			tmp.li = va_arg(ap, long int);
			*d = tmp.li;
		}
	if (str[0] != 'l' && str[0] != 'h' && str[0] != 'L')
		{
			tmp.i = va_arg(ap, int);
			*d = tmp.i;
		}
}
void ft_get_size_u(char *str, unsigned long long int *d, va_list ap)
{
	char *s[5];
	
	ft_gettab(&s, 5);
	t_type_u tmp;

	s[3] = "";
	s[4] = "";
	ft_chkflags(&str, s);
	if (str[0] == 'l' && str [1] == 'l')
		{
			tmp.lli = va_arg(ap, long long int);
			*d = tmp.lli;
		}
	if (str[0] == 'h' && str [1] == 'h')
		{
			tmp.c =  va_arg(ap, int);
			*d = tmp.c;
		}
	ft_get_size_u_part2(str, d, ap);
}


int ft_number(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	long long int d;

	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	(*str)->content = 0;
	ft_shiftarg(n, ap); //тут оставим или перенесем не знаю
	ft_get_size(s, &d, ap);
	if (!(s1 = ft_itoa_base(d, 10)))
		{
			free(s);
			return (0);
		}
	(*str)->content = s1;
	(*str)->content_size = ft_strlen(s1);
	if (!(ft_fmt_plus(str, s)) ||\
		!(ft_fmt_prec(str, s)) ||\
		!(ft_fmt_width(str, s)))
		{
			free(s);
			return (0);
		}
	free(s);
	return (1);
}

int ft_number_o(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	long long int d;

	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	(*str)->content = 0;
	ft_shiftarg(n, ap); //тут оставим или перенесем не знаю
	ft_get_size(s, &d, ap);
	if (!(s1 = ft_itoa_base_u(d, 8)))
		{
			free(s);
			return (0);
		}
	(*str)->content = s1;
	(*str)->content_size = ft_strlen(s1);
	if (!(ft_fmt_plus(str, s)) ||\
		!(ft_fmt_prec(str, s)) ||\
		!(ft_fmt_width(str, s)))
		{
			free(s);
			return (0);
		}
	free(s);
	return (1);
}
int ft_number_x(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	unsigned long long int d;

	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	(*str)->content = 0;
	ft_shiftarg(n, ap); //тут оставим или перенесем не знаю
	ft_get_size_u(s, &d, ap);
	if (!(s1 = ft_itoa_base_u(d, 16)))
		{
			free(s);
			return (0);
		}
	(*str)->content = s1;
	(*str)->content_size = ft_strlen(s1);
	if (!(ft_fmt_prec(str, s)) ||\
		!(ft_fmt_width(str, s)))
		{
			free(s);
			return (0);
		}
	s[ft_strlen(s) - 1] == 'x' ? ft_fmt_lowc(str) : s;
	free(s);
	return (1);
}

int ft_number_u(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	unsigned long long int d;

	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	(*str)->content = 0;
	ft_shiftarg(n, ap); //тут оставим или перенесем не знаю
	ft_get_size_u(s, &d, ap);
	if (!(s1 = ft_itoa_base_u(d, 10)))
		{
			free(s);
			return (0);
		}
	(*str)->content = s1;
	(*str)->content_size = ft_strlen(s1);
	if (!(ft_fmt_prec(str, s)) ||\
		!(ft_fmt_width(str, s)))
		{
			free(s);
			return (0);
		}
	free(s);
	return (1);
}

/* int ft_number(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	int d;

	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	free((*str)->content);
	ft_shiftarg(n, ap);
	d = va_arg(ap, int);
	if (!(s1 = ft_itoa(d)))
		{
			free(s);
			return (0);
		}
	(*str)->content = s1;
	(*str)->content_size = ft_strlen(s1);
	if (!(ft_fmt_plus(str, s)) ||\
		!(ft_fmt_prec(str, s)) ||\
		!(ft_fmt_width(str, s)))
		{
			free(s);
			return (0);
		}
	free(s);
	return (1);
}
 */
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
	void (*del)(void *, size_t);
	int n;

	del = &ft_cleanup;
	str = 0;
	if (ft_readformat(&str, (char *)format) == -1) //получили спискок строк вида строка строка формат строка и т.д.
	{
	str ? ft_lstdel(&str, del) : str;
		return (0);
	}
	va_start(ap, format);
	if (ft_format(&str, 0, ap) == 0) //получили спискок строк вида строка строка формат строка и т.д.
	{
	str ? ft_lstdel(&str, del) : str;
		return (0);
	}
	va_end(ap);
	n = ft_printstr(str);
	str ? ft_lstdel(&str, del) : str;
	return (n);
}
