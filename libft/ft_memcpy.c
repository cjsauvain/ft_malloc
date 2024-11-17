/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:38:10 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/09 12:18:51 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const char	*cast;
	char		*cast2;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	cast = src;
	cast2 = dest;
	while (i < n)
	{
		cast2[i] = cast[i];
		i++;
	}
	return (dest);
}
