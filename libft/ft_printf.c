/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:37:50 by jsauvain          #+#    #+#             */
/*   Updated: 2022/07/14 12:16:58 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	arg;

	i = 0;
	va_start(arg, format);
	i += ft_format(format, arg);
	va_end(arg);
	return (i);
}
