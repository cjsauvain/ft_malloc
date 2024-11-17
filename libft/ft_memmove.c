/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:38:32 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/05 11:31:34 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*cast;
	char		*cast2;
	size_t		i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	cast = src;
	cast2 = dest;
	if (src < dest)
	{
		while (n-- > i)
			cast2[n] = cast[n];
	}
	else if (src > dest)
	{
		while (i++ < n)
			cast2[i - 1] = cast[i - 1];
	}
	else if (src == dest)
	{
		cast2[i] = cast[i];
		i++;
	}
	return (dest);
}
