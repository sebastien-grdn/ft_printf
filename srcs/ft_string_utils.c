/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:16:36 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/15 11:17:06 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(va_list args, t_syntax *syntax)
{
	int len;
	char *substring;
	char padding;
	int i;

	padding = ' ';
	if (syntax->zeros)
		padding = '0';
	substring = va_arg(args, char *);
	if (!substring)
	{
		substring = malloc(sizeof(char) * 7);
		substring = "(null)\0";
	}
	len = 0;
	while (substring[len])
		len++;
	if (syntax->precision_set && len > syntax->precision)
		len = syntax->precision;
	i = len;
	while (syntax->width > i && !syntax->justify_left)
	{
		write(1, &padding, 1);
		i++;
	}
	if (syntax->precision_set && syntax->precision < len)
	{
		write(1, substring, syntax->precision);
		return (i - len + syntax->precision);
	}
	write(1, substring, len);
	while (syntax->width > i)
	{
		write(1, " ", 1);
		i++;
	}
	return (i);
}