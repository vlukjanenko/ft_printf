/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 17:52:40 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 20:04:53 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	i;
	size_t	src_len;
	size_t	result;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	result = dst_len + src_len;
	if (size < dst_len)
		return (size + src_len);
	while (dst_len < size && src[i])
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	if (dst_len == size)
		dst[size - 1] = 0;
	else
		dst[dst_len] = 0;
	return (result);
}
