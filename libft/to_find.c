/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 18:14:35 by jsauvain          #+#    #+#             */
/*   Updated: 2022/07/14 12:12:59 by jsauvain         ###   ########.fr       */
/*   Created: 2022/04/13 10:58:11 by jsauvain          #+#    #+#             */
/*   Updated: 2022/04/27 10:40:46 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	to_find(const char *format, char c, va_list arg)
{
	int	i;

	i = 0;
	while (*format)
	{
		if (*format == c)
		{
			i += ft_formatting(format, arg);
			format += 2;
		}
		else
		{
			i += ft_putchar(*format);
			format++;
		}
	}
	return (i);
}
