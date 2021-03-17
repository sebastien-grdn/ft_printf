/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:43:39 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/17 11:27:21 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_arg(const char *format, int *i, va_list args, t_syntax *syntax)
{
	int len;

	len = 0;
	if (format[*i] == 's')
		len = print_string(args, syntax);
	else if (ft_strchr("di", format[*i]))
		len = print_decimal(args, syntax);
	else if (format[*i] == 'u')
		len = print_unsigned(args, syntax);
	else if (format[*i] == 'c')
		len = print_char(args, syntax);
	else if (format[*i] == 'p')
		len = print_pointer(args, syntax);
	else if (ft_strchr("xX", format[*i]))
		len = print_hexa(args, format[*i], syntax);
	else if (format[*i] == '%')
		len = (print_modulo(syntax));
	*i = *i + 1;
	return (len);
}

int		ft_printf(const char *format, ...)
{
	int			i;
	int			len;
	va_list		args;
	t_syntax	syntax;
	int			return_value;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
		if (format[i] != '%')
		{
			write(1, &format[i++], 1);
			len++;
		}
		else if (format[i++] == '%')
		{
			extract_syntax(format, &i, &syntax, args);
			return_value = print_arg(format, &i, args, &syntax);
			if (return_value == -1)
				return (len);
			len += return_value;
		}
	va_end(args);
	return (len);
}
