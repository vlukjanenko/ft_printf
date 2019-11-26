/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2019/11/26 20:10:02 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
void ft_shiftarg(int n, va_list ap)
{
	int i;

	i = 0;
	while (i++ < n)
		va_arg(ap, char *);
}

void ft_cleanflags(char *(*ftab)[5])
{
	(*ftab)[0] = "";
	(*ftab)[1] = "";
	(*ftab)[2] = "";
	(*ftab)[3] = "";
	(*ftab)[4] = "";

}

int ft_minus(char *str)
{
	if (ft_strchr(str, '-'))
		return (1);
	return (0);
}


void ft_skipflags(char **str)
{
	char *flags[5];

	ft_cleanflags(&flags);
	flags[0] = " #0-+";
	ft_chkflags(str, flags);
}

int ft_width(char *str)
{
	int w;

	ft_skipflags(&str);
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

int ft_prec(char *str)
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
/* char *ft_fillstr(int f, int w, int p, char *str)
{
	char *rezult;
	int add;
	char *tmp;
	char *tmp2;

	if (!str)
		{
			rezult = ft_strdup("(null)");
			return (rezult);
		}
	if (p >= 0)
		rezult = ft_strsub(str, 0, p);
	else 
		rezult = ft_strdup(str);
	add = w - ft_strlen(rezult);
	if (add > 0)
	{
		tmp = ft_strnew(add);
		ft_memset(tmp, ' ', add);
		if (f == 0)
			tmp2 = ft_strjoin(tmp, rezult);
		else
			tmp2 = ft_strjoin(rezult, tmp);
		free(tmp);
		free(rezult);
		rezult = tmp2;	
	}
	return (rezult);
}
 */

/* int ft_sringflags(char *str)
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
} */

int ft_format_output(t_list **str, char *s)
{
	int w;
	int p;
	if (*str)
	{}
	w = ft_width(s);
	p = ft_prec(s);
	printf("width - |%d|", w);
	printf("prec  - |%d|", p);
	return (1);
}

int ft_string(t_list **str, int n, va_list ap)
{
	char *s;
	char *s1;
	
	if(!(s = ft_strsub((*str)->content, 1, (*str)->content_size - 1)))
		return (0);
	ft_shiftarg(n, ap);
	if (!(s1 = ft_strdup(va_arg(ap, char *))))
		return (0);
	free((*str)->content);
	(*str)->content = s1;
	free(s1); 
	(*str)->content_size = ft_strlen((*str)->content);
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
	return (1);
}
int ft_persent(t_list **str, int n, va_list ap)
{
	char *s;
	
	ft_shiftarg(n, ap);
	s = "%";
	free((*str)->content);
	if (!((*str)->content = ft_strdup(s)))
		return (0);
	(*str)->content_size = ft_strlen(s);
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
