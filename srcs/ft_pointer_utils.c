/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:25:18 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/15 11:25:29 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(va_list args, t_syntax *syntax)
{
	unsigned long x;
	int			hexa_length;
	char *	hexa;
	unsigned long			y;
	int lol;
	char padding;
	int precision_length;

	x = (unsigned long) va_arg(args, void*);
	y = x;
	hexa_length = 1;
	while (y/=16)
		hexa_length += 1;
	if (x == 0 && syntax->precision_set)
		hexa_length = 0;
	hexa = (char *)malloc(sizeof(char) * hexa_length + 1);
	hexa[hexa_length--] = '\0';
	y = x;
	while (y >= 16)
	{
		hexa[hexa_length--] = "0123456789abcdef"[y % 16];
		y /= 16;
	}
	if (!(x == 0 && syntax->precision_set))
		hexa[hexa_length] = "0123456789abcdef"[y];
	hexa_length = ft_strlen(hexa);
	precision_length = 0;
	while (syntax->precision_set && (hexa_length + precision_length) < syntax->precision)
		precision_length++;
	padding = ' ';
	if (syntax->zeros && !syntax->precision_set)
		padding = '0';
	lol = precision_length;
	if (padding == '0')
		write(1, "0x", 2);
	while (!syntax->justify_left && hexa_length + precision_length + 2 < syntax->width)
	{
		write(1, &padding, 1);
		lol++;
		syntax->width--;
	}
	if (padding == ' ')
		write(1, "0x", 2);
	while (!syntax->justify_left && hexa_length + precision_length + 2 < syntax->width)
	{
		write(1, &padding, 1);
		lol++;
		syntax->width--;
	}
	while (precision_length--)
		write(1, "0", 1);
	write(1, hexa, hexa_length);
	while (lol + hexa_length + 2 < syntax->width)
	{
		write(1, " ", 1);
		lol++;
	}
	free(hexa);
	return (2 + hexa_length + lol);
}