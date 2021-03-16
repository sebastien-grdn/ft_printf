/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:28:50 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/16 18:38:03 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_utoa(unsigned int n)
{
	int				size;
	unsigned int	x;
	char			*str;

	size = 1;
	x = n;
	while ((x /= 10) > 0)
		size += 1;
	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[size--] = '\0';
	x = n;
	if (x == 0)
		str[0] = '0';
	while (x)
	{
		str[size--] = (x % 10) + 48;
		x /= 10;
	}
	return (str);
}

int		set_padding(int input, char *padding, t_syntax *syntax)
{
	*padding = ' ';
	if (syntax->precision_set && syntax->precision == 0 && input != 0)
	{
		syntax->precision_set = false;
		syntax->zeros = false;
	}
	if (syntax->zeros && !syntax->precision_set)
		*padding = '0';
	return (1);
}

int		print_unsigned(va_list args, t_syntax *syntax)
{
	int				len;
	char			*int_string;
	char			padding;
	int				extra_len;
	unsigned int	input;

	extra_len = 0;
	input = (unsigned int)va_arg(args, int);
	int_string = ft_utoa(input);
	len = ft_strlen(int_string);
	set_padding(input, &padding, syntax);
	extra_len += padding_sign_precision(syntax, false, &len, padding);
	if (!(syntax->precision_set && syntax->precision == 0))
		write(1, int_string, ft_strlen(int_string));
	else
		len = 0;
	while (len < syntax->width--)
	{
		write(1, " ", 1);
		extra_len++;
	}
	free(int_string);
	return (len + extra_len);
}
