/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:21:45 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/18 14:03:26 by sg9031           ###   ########.fr       */
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

char	*extract_hexa_string(va_list args, t_syntax *syntax, char flag)
{
	long int	x;
	long int	y;
	int			len;
	char		*hexa_string;

	x = va_arg(args, unsigned int);
	y = x;
	len = 1;
	while (y /= 16)
		len++;
	if (x == 0 && syntax->precision_set)
		len = 0;
	hexa_string = (char *)malloc(sizeof(char) * len + 1);
	hexa_string[len--] = '\0';
	y = x;
	while (y >= 16)
	{
		hexa_string[len--] = "0123456789abcdef"[y % 16];
		y /= 16;
	}
	if (!(x == 0 && syntax->precision_set))
		hexa_string[len] = "0123456789abcdef"[y];
	if (flag == 'X')
		to_upper_string(hexa_string);
	return (hexa_string);
}

int		print_complete_hexa(char *hexa_string,
	t_syntax *syntax, char padding, int precision_length)
{
	int	padding_precision_len;
	int	len;

	len = ft_strlen(hexa_string);
	padding_precision_len = precision_length;
	while (!syntax->justify_left && len + precision_length < syntax->width)
	{
		write(1, &padding, 1);
		padding_precision_len++;
		syntax->width--;
	}
	while (precision_length--)
		write(1, "0", 1);
	write(1, hexa_string, len);
	while (padding_precision_len + len < syntax->width)
	{
		write(1, " ", 1);
		padding_precision_len++;
	}
	free(hexa_string);
	return (len + padding_precision_len);
}

int		print_hexa(va_list args, char flag, t_syntax *syntax)
{
	int		len;
	char	*hexa_string;
	int		total_length;
	char	padding;
	int		precision_length;

	hexa_string = extract_hexa_string(args, syntax, flag);
	len = ft_strlen(hexa_string);
	precision_length = 0;
	while (syntax->precision_set &&
		(len + precision_length) < syntax->precision)
		precision_length++;
	padding = ' ';
	if (syntax->zeros && !syntax->precision_set)
		padding = '0';
	total_length = print_complete_hexa(hexa_string,
		syntax, padding, precision_length);
	return (total_length);
}
