/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:21:45 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/15 11:23:13 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	to_upper_string(char *string)
{
	int i;

	i = -1;
	while (string[++i])
		string[i] = ft_toupper(string[i]);
	return ;
}

int	print_hexa(va_list args, char flag, t_syntax *syntax)
{
	long int		x;
	long int		y;
	int		hexa_length;
	char *	hexa;
	int	lol;
	char padding;
	int precision_length;
	
	x = va_arg(args, long int);
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
	if (flag == 'X')
		to_upper_string(hexa);
	precision_length = 0;
	while (syntax->precision_set && (hexa_length + precision_length) < syntax->precision)
		precision_length++;
	padding = ' ';
	if (syntax->zeros && !syntax->precision_set)
		padding = '0';
	lol = precision_length;
	while (!syntax->justify_left && hexa_length + precision_length < syntax->width)
	{
		write(1, &padding, 1);
		lol++;
		syntax->width--;
	}
	while (precision_length--)
		write(1, "0", 1);
	write(1, hexa, hexa_length);
	while (lol + hexa_length < syntax->width)
	{
		write(1, " ", 1);
		lol++;
	}
	free(hexa);
	return hexa_length + lol;
}