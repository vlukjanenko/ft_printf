/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 18:35:31 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 16:41:34 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sstr;

	if (!s)
		return (NULL);
	sstr = ft_strnew(len);
	if (sstr == NULL)
		return (NULL);
	ft_strncpy(sstr, s + start, len);
	return (sstr);
}
