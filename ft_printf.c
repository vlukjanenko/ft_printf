/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:34:22 by majosue           #+#    #+#             */
/*   Updated: 2020/11/06 22:13:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

const char	g_flag_tab[NBR_FLAGS + 1] =
{' ', '#', '0', '-', '+', '\0'};
const char	g_modi_tab[NBR_MODS + 1] =
{'c', 's', 'p', 'd', 'i', 'o', 'u', 'x', 'X', 'f', '%', '\0'};

void	ft_exit(void)
{
	ft_putendl_fd("ERROR", 2);
	exit(-1);
}

void	ft_printstr(int fd, char *str, size_t len, int *n)
{
	static size_t	s_n = 0;
	static char		buffer[BUFSIZE + 1] = {0};

	if (len == 0 || s_n + len > BUFSIZE)
	{
		if (write(fd, buffer, s_n) < 0)
			ft_exit();
		s_n = 0;
		buffer[0] = 0;
	}
	while (len > BUFSIZE)
	{
		if (write(fd, str, BUFSIZE) < 0)
			ft_exit();
		str += BUFSIZE;
		len -= BUFSIZE;
		*n += len;
	}
	if (str)
	{
		ft_memcpy(&buffer[s_n], str, len);
		s_n += len;
		*n += len;
	}
}

int		ft_printf(const char *restrict format, ...)
{
	va_list ap;
	int		n;

	n = 0;
	va_start(ap, format);
	if (ft_readformat(1, &n, (char *)format, ap) == -1)
		ft_exit();
	va_end(ap);
	ft_printstr(1, NULL, 0, &n);
	return (n);
}

int		ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list ap;
	int		n;

	n = 0;
	va_start(ap, format);
	if (ft_readformat(fd, &n, (char *)format, ap) == -1)
		ft_exit();
	va_end(ap);
	ft_printstr(fd, NULL, 0, &n);
	return (n);
}
