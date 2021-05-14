/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:53:30 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 16:37:20 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char			*nstr;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	nstr = ft_strnew(ft_strlen(s));
	if (nstr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	return (nstr);
}
