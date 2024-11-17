/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 19:01:25 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/12 15:45:43 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*copy;

	copy = s;
	while (*s)
		s++;
	while (*s != (unsigned char)c && s != copy)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s--;
	}
	if (*s != (unsigned char)c && c != '\0')
		return (0);
	return ((char *)s);
}
