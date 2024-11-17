/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:14:35 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/05 11:30:23 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little [0])
		{
			j = 0;
			while (little[j] == big[i] && little[j] && i < len)
			{
				i++;
				j++;
			}
			if (little[j] == '\0')
				return ((char *)(big + i - j));
			i -= j;
		}
		i++;
	}
	return (NULL);
}
