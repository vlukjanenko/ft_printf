/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:17:59 by majosue           #+#    #+#             */
/*   Updated: 2019/11/25 16:53:05 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# define CONVERSIONS "cspdiouxXf%"

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
int 	ft_persent(t_list **str, int n, va_list ap);
int     ft_compare(char *flags, char c);
void	ft_gettab(char *(*ftab)[5]);


#endif
