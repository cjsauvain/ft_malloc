/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hexa_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:53:58 by jsauvain          #+#    #+#             */
/*   Updated: 2022/05/09 17:21:12 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_hexa_ptr(unsigned long long ptr, int i)
{
	if (ptr >= 16)
	{
		put_hexa_ptr(ptr / 16, i);
		put_hexa_ptr(ptr % 16, i);
	}
	else if (ptr < 16)
	{
		i++;
		if (ptr % 16 <= 9)
			ft_putchar((ptr % 16) + '0');
		else if (ptr % 16 >= 10 && ptr % 16 <= 15)
			ft_putchar((ptr % 16) + 'W');
	}
	return (i);
}
