/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:05:17 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 16:40:57 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	nl;

	nl = ft_strlen(needle);
	if (!needle || nl > ft_strlen(haystack))
		return (NULL);
	while (ft_strlen(haystack) >= nl)
	{
		if (ft_strncmp(needle, haystack, nl) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
