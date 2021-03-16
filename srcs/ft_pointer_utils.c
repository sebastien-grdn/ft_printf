/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:25:18 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/16 18:21:00 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*extract_pointer_string(va_list args,
	t_syntax *syntax)
{
	unsigned long	x;
	unsigned long	y;
	int				len;
	char			*pointer_string;

	x = (unsigned long)va_arg(args, void*);
	y = x;
	len = 1;
	while (y /= 16)
		len++;
	if (x == 0 && syntax->precision_set)
		len = 0;
	pointer_string = (char *)malloc(sizeof(char) * len + 1);
	pointer_string[len--] = '\0';
	y = x;
	while (y >= 16)
	{
		pointer_string[len--] = "0123456789abcdef"[y % 16];
		y /= 16;
	}
	if (!(x == 0 && syntax->precision_set))
		pointer_string[len] = "0123456789abcdef"[y];
	return (pointer_string);
}

int		print_before_pointer(char padding, t_syntax *syntax,
	int len, int precision_length)
{
	int padding_precision_len;

	padding_precision_len = precision_length;
	if (padding == '0')
		write(1, "0x", 2);
	while (!syntax->justify_left && len + precision_length + 2 < syntax->width)
	{
		write(1, &padding, 1);
		padding_precision_len++;
		syntax->width--;
	}
	if (padding == ' ')
		write(1, "0x", 2);
	while (!syntax->justify_left &&
		len + precision_length + 2 < syntax->width)
	{
		write(1, &padding, 1);
		padding_precision_len++;
		syntax->width--;
	}
	return (padding_precision_len);
}

int		print_complete_pointer(char *pointer_string,
	t_syntax *syntax, char padding, int precision_length)
{
	int	padding_precision_len;
	int	len;

	len = ft_strlen(pointer_string);
	padding_precision_len = print_before_pointer(
		padding, syntax, len, precision_length);
	while (precision_length--)
		write(1, "0", 1);
	write(1, pointer_string, len);
	while (padding_precision_len + len + 2 < syntax->width)
	{
		write(1, " ", 1);
		padding_precision_len++;
	}
	free(pointer_string);
	return (len + padding_precision_len + 2);
}

int		print_pointer(va_list args, t_syntax *syntax)
{
	char	*pointer_string;
	char	padding;
	int		precision_length;
	int		pointer_length;
	int		total_length;

	pointer_string = extract_pointer_string(args, syntax);
	pointer_length = ft_strlen(pointer_string);
	precision_length = 0;
	while (syntax->precision_set &&
		(pointer_length + precision_length) < syntax->precision)
		precision_length++;
	padding = ' ';
	if (syntax->zeros && !syntax->precision_set)
		padding = '0';
	total_length = print_complete_pointer(pointer_string,
		syntax, padding, precision_length);
	return (total_length);
}
