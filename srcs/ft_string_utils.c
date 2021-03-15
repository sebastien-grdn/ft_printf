/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:16:36 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/15 12:37:23 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*extract_substring(va_list args, int *len)
{
	char *substring;

	substring = va_arg(args, char *);
	if (!substring)
	{
		substring = malloc(sizeof(char) * 7);
		substring = "(null)\0";
	}
	*len = ft_strlen(substring);
	return (substring);
}

int		print_string(va_list args, t_syntax *syntax)
{
	int		len;
	char	*substring;
	char	padding;
	int		i;

	padding = ' ';
	if (syntax->zeros)
		padding = '0';
	substring = extract_substring(args, &len);
	if (syntax->precision_set && len > syntax->precision)
		len = syntax->precision;
	i = len;
	while (syntax->width > i++ && !syntax->justify_left)
		write(1, &padding, 1);
	i--;
	if (syntax->precision_set && syntax->precision < len)
	{
		write(1, substring, syntax->precision);
		return (i - len + syntax->precision);
	}
	write(1, substring, len);
	i--;
	while (syntax->width > ++i)
		write(1, " ", 1);
	return (i);
}
