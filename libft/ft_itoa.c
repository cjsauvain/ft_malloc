/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:21:41 by jsauvain          #+#    #+#             */
/*   Updated: 2022/09/26 11:04:06 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_malloc(int n)
{
	char	*src;
	int		i;
	int		n_copy;

	i = 1;
	n_copy = n;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		i++;
	}
	if (n_copy < 0)
		src = malloc((i + 2) * sizeof(char));
	else
		src = malloc((i + 1) * sizeof(char));
	return (src);
}

char	*ft_reverse(char *src)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	j--;
	while (i < j)
	{
		c = src[i];
		src[i++] = src[j];
		src[j--] = c;
	}
	return (src);
}

char	*ft_itoa(int n)
{
	char	*src;
	int		i;
	int		n_copy;

	i = 0;
	n_copy = n;
	src = ft_malloc(n);
	if (src == NULL)
		return (src);
	else if (n == 0)
		return ("0");
	else if (n == -2147483648)
		return ("-2147483648");
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		src[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (n_copy < 0)
		src[i++] = '-';
	src[i] = '\0';
	return (ft_reverse(src));
}
