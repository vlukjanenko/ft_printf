/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 07:52:08 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 16:33:45 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cstr;

	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(s1) > (ft_strlen(s1) + ft_strlen(s2)) || \
ft_strlen(s2) > (ft_strlen(s1) + ft_strlen(s2)))
		return (NULL);
	cstr = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (cstr == NULL)
		return (NULL);
	cstr = ft_strcpy(cstr, s1);
	return (ft_strcat(cstr, (char *)s2));
}
