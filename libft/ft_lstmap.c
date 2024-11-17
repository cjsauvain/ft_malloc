/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:36:41 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/12 15:07:24 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void(*del)(void *))
{
	t_list	*tmp;
	t_list	*ret;

	tmp = ft_lstnew((f)(lst->content));
	ret = tmp;
	if (tmp == NULL)
		return (tmp);
	while (lst->next != 0)
	{
		lst = lst->next;
		tmp->next = ft_lstnew((f)(lst->content));
		if (tmp->next == NULL)
			ft_lstclear(&ret, del);
		tmp = tmp->next;
	}
	tmp = 0;
	return (ret);
}
