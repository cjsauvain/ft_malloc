/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:38:28 by jsauvain          #+#    #+#             */
/*   Updated: 2022/05/09 16:20:25 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	up_hexa(unsigned int n, int i)
{
	if (n >= 16)
	{
		i++;
		up_hexa(n / 16, i);
		up_hexa(n % 16, i);
	}
	else if (n < 16)
	{
		i++;
		if (n % 16 <= 9)
			ft_putchar((n % 16) + '0');
		else if (n % 16 == 10)
			ft_putchar('A');
		else if (n % 16 == 11)
			ft_putchar('B');
		else if (n % 16 == 12)
			ft_putchar('C');
		else if (n % 16 == 13)
			ft_putchar('D');
		else if (n % 16 == 14)
			ft_putchar('E');
		else if (n % 16 == 15)
			ft_putchar('F');
	}
	return (i);
}
