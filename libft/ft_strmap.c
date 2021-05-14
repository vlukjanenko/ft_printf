/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:12:25 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 16:36:33 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f) (char))
{
	char	*nstr;
	char	*tmp;

	if (!s || !f)
		return (NULL);
	nstr = ft_strnew(ft_strlen(s));
	if (nstr == NULL)
		return (NULL);
	tmp = nstr;
	while (*s != '\0')
		*nstr++ = f(*s++);
	return (tmp);
}
