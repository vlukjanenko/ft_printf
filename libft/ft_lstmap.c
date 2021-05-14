/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majosue <majosue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:03:56 by majosue           #+#    #+#             */
/*   Updated: 2021/05/12 16:10:09 by majosue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*set_tmp(t_list **tmp, void *(*f) (t_list *elem), t_list *lst)
{
	*tmp = f(lst);
	return (*tmp);
}

t_list	*ft_lstmap(t_list *lst, void *(*f) (t_list *elem))
{
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = NULL;
	if (lst->next != NULL)
	{
		if (!set_tmp(&tmp, f, lst))
			return (NULL);
		tmp->next = ft_lstmap(lst->next, f);
		if (!tmp->next)
		{
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
	else
	{
		if (!set_tmp(&tmp, f, lst))
			return (NULL);
	}
	return (tmp);
}
