/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 10:56:58 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/09 11:16:57 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned const char	*src1;
	unsigned const char	*src2;

	i = 0;
	src1 = (unsigned const char *)s1;
	src2 = (unsigned const char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && src1[i] == src2[i])
		i++;
	return (src1[i] - src2[i]);
}
