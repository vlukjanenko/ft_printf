/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:17:59 by majosue           #+#    #+#             */
/*   Updated: 2019/11/29 13:09:17 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>

typedef int (*t_fun)(t_list**, int, va_list);

int 	ft_printf(const char *restrict format, ...);
/* validator format string */
int		ft_chkflags(char **str, char *ftab[5]);
/* push element to end of list */
int		ft_lstp2back(t_list **begin_list, void const *content, size_t content_size);
/* save ft_printf format string in list (separated %) */
int		ft_readformat(t_list **str, char *format);
/* fill tab of pinters to functions */
t_fun	ft_get_f(char c);
/* conversion functions */
int		ft_char(t_list **str, int n, va_list ap);
int		ft_string(t_list **str, int n, va_list ap);
int 	ft_pointer(t_list **str, int n, va_list ap);
int 	ft_number(t_list **str, int n, va_list ap);
int 	ft_float(t_list **str, int n, va_list ap);
int 	ft_percent(t_list **str, int n, va_list ap);
int     ft_compare(char *flags, char c);
void	ft_gettab(char *(*ftab)[5], int index);
void	ft_add_left(t_list **str, void **newstr, size_t w, char c);
void	ft_add_right(t_list **str, void **newstr, size_t w, char c);
void	ft_shiftarg(int n, va_list ap);
int	    ft_null(char *str);
int 	ft_space(char *str);
int 	ft_minus(char *str);
int		ft_plus(char *str);
int		ft_skipflags(char **str);
int		ft_width(char *str, size_t *w);
int		ft_prec(char *str, size_t *p);
int		ft_fmt_char(t_list **str, char *s);
int		ft_fmt_plus(t_list **str, char *s);





#endif
