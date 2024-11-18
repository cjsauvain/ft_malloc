/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:37:35 by jsauvain          #+#    #+#             */
/*   Updated: 2024/11/18 12:05:44 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formatting(const char *str, va_list arg)
{
	int	i;

	i = 0;
	if (str[1] == 'c')
		i += ft_putchar(va_arg(arg, int));
	else if (str[1] == 's')
		i += ft_putstr(va_arg(arg, char *));
	else if (str[1] == 'p')
	{
		i += 2;
		ft_putstr("0x");
		i += put_hexa_ptr(va_arg(arg, unsigned long long), i);
	}
	else if (str[1] == 'i' || str[1] == 'd')
		i += ft_putnbr(va_arg(arg, int), i);
	else if (str[1] == 'u')
		i += ft_putnbr(va_arg(arg, unsigned int), i);
	else if (str[1] == 'x')
		i += low_hexa(va_arg(arg, unsigned int), i);
	else if (str[1] == 'X')
		i += up_hexa(va_arg(arg, unsigned int), i);
	else if (str[1] == '%')
	{
		write(1, "%", 1);
		i++;
	}
	return (i);
}

int	ft_format(const char *str, va_list arg)
{
	int	i;

	i = 0;
	i += to_find(str, '%', arg);
	return (i);
}
