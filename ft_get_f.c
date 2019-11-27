/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:51:47 by majosue           #+#    #+#             */
/*   Updated: 2019/11/27 17:52:11 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Return function pointer
*/

t_fun	ft_get_f(char c)
{
	int		i;
	t_fun	ftab[11];
	char *s[5];

	ft_gettab(&s, 4);
	i = 0;
	while (s[4][i] && s[4][i] != c)
		i++;
	ftab[0] = &ft_char;
	ftab[1] = &ft_string;
	/* ftab[2] = &ft_pointer; */
	ftab[3] = &ft_number;
	ftab[4] = &ft_number;
	ftab[5] = &ft_number;
	ftab[6] = &ft_number;
	ftab[7] = &ft_number;
	ftab[8] = &ft_number;
	/* ftab[9] = &ft_float; */
	ftab[10] = &ft_persent;
	return (ftab[i]);
}
