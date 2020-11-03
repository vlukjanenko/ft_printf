/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readformat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:10:10 by majosue           #+#    #+#             */
/*   Updated: 2020/11/03 05:15:57 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_save_before_ptr(t_list **str, char **ptr, char **format)
{
	t_fmt	chain;

	ft_bzero(&chain, sizeof(chain));
	if (*ptr == *format)
		return (0);
	chain.str = *format;
	chain.len = *ptr - *format;
	if (!(ft_lstp2back(str, &chain, sizeof(chain))))
		return (-1);
	*format = *ptr;
	return (1);
}

int	ft_save_after_ptr(t_list **str, char **ptr, char **format, va_list ap)
{
	t_fmt	chain;
	t_fun	f;

	ft_bzero(&chain, sizeof(chain));
	(*ptr)++;
	if (!ft_chkflags(ptr, &chain, ap))
	{
		*format = *ptr;
		return (1);
	}
	f = ft_get_f(chain.modi);
	f(&chain, ap);
	if (!(ft_lstp2back(str, &chain, sizeof(chain))))
		return (-1);
	*format = *ptr;
	return (1);
}

int	ft_readformat(t_list **str, char *format, va_list ap)
{
	char	*ptr;
	t_fmt	chain;

	ft_bzero(&chain, sizeof(chain));
	if (!*format)
		return (0);
	if ((ptr = ft_strchr(format, '%')))
	{
		if ((ft_save_before_ptr(str, &ptr, &format)) == -1)
			return (-1);
		if (ft_save_after_ptr(str, &ptr, &format, ap) == -1)
			return (-1);
		return (ft_readformat(str, format, ap));
	}
	chain.str = format;
	chain.len = ft_strlen(format);
	if (!(ft_lstp2back(str, &chain, sizeof(chain))))
		return (-1);
	return (1);
}
