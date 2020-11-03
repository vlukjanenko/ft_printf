/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 20:17:59 by majosue           #+#    #+#             */
/*   Updated: 2020/11/04 00:54:31 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

# define BUFSIZE		512

# define NBR_FLAGS		5

# define SPACE			0
# define SHARP			1
# define ZERO			2
# define MINUS			3
# define PLUS			4

# define NBR_MODS		11

# define C_MOD			0
# define S_MOD			1
# define P_MOD			2
# define D_MOD			3
# define I_MOD			4
# define O_MOD			5
# define U_MOD			6
# define X_SMALL_MOD	7
# define X_BIG_MOD		8
# define F_MOD			9
# define PERSENT_MOD	10

typedef union	u_type {
	int				i;
	char			c;
	short int		si;
	long int		li;
	long long int	lli;
}				t_type;

typedef union	u_type_u {
	unsigned int			i;
	unsigned char			c;
	unsigned short int		si;
	unsigned long int		li;
	unsigned long long int	lli;
}				t_type_u;

typedef struct	s_fmt
{
	int			str_need_free;
	char		*str;
	char		arg_size[3];
	int			modi;
	size_t		len;
	int			flag[NBR_FLAGS];
	size_t		widt[2];
	size_t		prec[2];
	int			fd;
}				t_fmt;

extern const char g_flag_tab[NBR_FLAGS + 1];
extern const char g_modi_tab[NBR_MODS + 1];

typedef int		(*t_fun)(t_fmt *, va_list);
int				ft_printf(const char *restrict format, ...);
int				ft_chkflags(char **str, t_fmt *chain, va_list ap);
t_list			*ft_lstp2back(t_list **begin_list, void const *content,\
size_t content_size);
int				ft_readformat(int *n, char *format, va_list ap);
t_fun			ft_get_f(int idx);
void			ft_exit(void);

/*
** conversion functions start
*/

int				ft_char(t_fmt *chain, va_list ap);
int				ft_string(t_fmt *chain, va_list ap);
int				ft_pointer(t_fmt *chain, va_list ap);
int				ft_number(t_fmt *chain, va_list ap);
int				ft_number_o(t_fmt *chain, va_list ap);
int				ft_number_u(t_fmt *chain, va_list ap);
int				ft_number_x(t_fmt *chain, va_list ap);
int				ft_float(t_fmt *chain, va_list ap);

/*
** conversion functions end
*/

void			ft_gettab(char *(*ftab)[5], int index);
void			ft_add_left(t_fmt *chain, void **newstr, size_t w, char c);
void			ft_add_right(t_fmt *chain, void **newstr, size_t w, char c);
int				ft_width(t_fmt *chain, size_t *w);
int				ft_prec(t_fmt *chain, size_t *p);
int				ft_fmt_char(t_fmt *chain);
int				ft_fmt_plus(t_fmt *chain);
int				ft_fmt_width(t_fmt *chain);
int				ft_fmt_prec(t_fmt *chain);
char			*ft_itoa_base(long long int value, int base);
char			*ft_itoa_base_u(unsigned long long int value, int base);
char			*ft_ftoa(long double n, int p);
void			ft_get_size(char *str, long long int *d, va_list ap);
void			ft_get_size_u(char *str, unsigned long long int *d, va_list ap);
void			ft_printstr(char *str, size_t len, int *n);

#endif
