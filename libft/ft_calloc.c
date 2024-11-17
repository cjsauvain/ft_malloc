/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:28:05 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/09 11:43:42 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*calloc;
	char	*cast;

	i = 0;
	if (size <= 4294967295 || nmemb <= 4294967295)
	{
		calloc = malloc(nmemb * size);
		cast = calloc;
		if (calloc == NULL)
			return (calloc);
		while (i < nmemb * size)
		{
			cast[i] = 0;
			i++;
		}
		return (calloc);
	}
	return (NULL);
}
