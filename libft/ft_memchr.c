/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 12:48:37 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/04 15:40:07 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n - 1 && *(unsigned char *)s != (unsigned char)c)
	{
		s++;
		i++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		return ((void *)s);
	else
		return (NULL);
}
