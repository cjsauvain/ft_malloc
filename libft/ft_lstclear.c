/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:05:46 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/12 14:26:07 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst != NULL)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst, (del));
			*lst = tmp;
		}
		lst = NULL;
	}
}
