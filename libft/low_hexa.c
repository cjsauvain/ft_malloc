/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   low_hexa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:38:26 by jsauvain          #+#    #+#             */
/*   Updated: 2022/05/09 16:20:19 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	low_hexa(unsigned int n, int i)
{
	if (n >= 16)
	{
		i++;
		low_hexa(n / 16, i);
		low_hexa(n % 16, i);
	}
	else if (n < 16)
	{
		i++;
		if (n % 16 <= 9)
			ft_putchar((n % 16) + '0');
		else if (n % 16 == 10)
			ft_putchar('a');
		else if (n % 16 == 11)
			ft_putchar('b');
		else if (n % 16 == 12)
			ft_putchar('c');
		else if (n % 16 == 13)
			ft_putchar('d');
		else if (n % 16 == 14)
			ft_putchar('e');
		else if (n % 16 == 15)
			ft_putchar('f');
	}
	return (i);
}
