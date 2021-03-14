/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 22:16:34 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/14 22:16:59 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(va_list args, t_syntax *syntax)
{
	unsigned char c;
	int i;
	char padding;

	padding = ' ';
	if (syntax->zeros)
		padding = '0';
	i = 1;
	if (syntax->width < 0)
	{
		syntax->width = -syntax->width;
		syntax->justify_left = true;
	}
	while (syntax->width > i++ && !syntax->justify_left)
		write(1, &padding, 1);
	c = va_arg(args, int);
	write(1, &c, 1);
	while (syntax->width >= i++)
		write(1, " ", 1);
	if (syntax->width)
		return (syntax->width);
	return (1);
}
