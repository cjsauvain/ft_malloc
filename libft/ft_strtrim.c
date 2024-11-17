/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:36:27 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/12 15:47:12 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(const char	*s1)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

static int	start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (set[j] == '\0')
			return (i);
		i++;
	}
	return (0);
}

static int	end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = len(s1) - 1;
	while (i > -1)
	{
		j = 0;
		while (s1[i] != set[j] && set[j])
			j++;
		if (set[j] == '\0')
			return ((len(s1) - 1) - ((len(s1) - 1) - i));
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		n;
	char	*dt;

	n = end(s1, set);
	j = 0;
	dt = malloc((end(s1, set) - start(s1, set) + 2) * sizeof(char));
	if (dt == NULL)
		return (NULL);
	i = start(s1, set);
	while (i <= n)
		dt[j++] = s1[i++];
	dt[j] = '\0';
	return (dt);
}
