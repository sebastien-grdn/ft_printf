/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:36:25 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/16 18:27:27 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*handle_min_max(void)
{
	int		i;
	char	*return_string;

	if (!(return_string = malloc(sizeof(char) * (11))))
		return (NULL);
	i = -1;
	while (++i < 11)
		return_string[i] = "2147483648\0"[i];
	return (return_string);
}

char	*extract_decimal(va_list args, t_syntax *syntax,
	int *lol, t_bool *negative)
{
	int		input;
	char	*int_string;

	int_string = NULL;
	*lol = 0;
	input = (int)va_arg(args, int);
	*negative = false;
	if (input < 0)
	{
		*negative = true;
		input = -input;
		*lol = *lol + 1;
	}
	if (input == INT_MIN || input - 1 == INT_MAX)
		int_string = handle_min_max();
	else
		int_string = ft_itoa(input);
	if (syntax->precision_set && syntax->precision == 0 && input != 0)
	{
		syntax->precision_set = false;
		syntax->zeros = false;
	}
	return (int_string);
}

int		print_decimal(va_list args, t_syntax *syntax)
{
	int		len;
	char	*int_string;
	char	padding;
	int		lol;
	t_bool	negative;

	int_string = extract_decimal(args, syntax, &lol, &negative);
	len = ft_strlen(int_string);
	padding = ' ';
	if (syntax->zeros && !syntax->precision_set)
		padding = '0';
	if (negative && syntax->width)
		syntax->width--;
	lol += padding_sign_precision(syntax, negative, &len, padding);
	if (!(syntax->precision_set && syntax->precision == 0))
		write(1, int_string, ft_strlen(int_string));
	else
		len = 0;
	while (len < syntax->width--)
	{
		write(1, " ", 1);
		lol++;
	}
	free(int_string);
	return (len + lol);
}
