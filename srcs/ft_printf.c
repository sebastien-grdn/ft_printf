/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:43:39 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/15 11:42:37 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_arg(const char *format, int *i, va_list args, t_syntax *syntax)
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

bool initialize_syntax(t_syntax *syntax)
{
	syntax->justify_left = false;
	syntax->zeros = false;
	syntax->width = 0;
	syntax->precision = 0;
	syntax->precision_set = false;
	return (true);
}

bool	extract_syntax(const char *format, int *i, t_syntax *syntax, va_list args)
{
	initialize_syntax(syntax);
	// FLAGS
	while (ft_strchr(FLAGS, format[*i]))
	{
		if (format[*i] == '0')
			syntax->zeros = true;
		else if (format[*i] == '-')
			syntax->justify_left = true;
		*i += 1;
	}
	// WIDTH
	if (format[*i] == '*')
	{
		syntax->width = va_arg(args, int);
		*i += 1;
	}
	while (ft_isdigit(format[*i]))
	{
		syntax->width = syntax->width * 10 + (format[*i] - 48);
		*i += 1;
	}
	// PRECISION
	if (format[*i] == '.')
	{
		syntax->precision_set = true;
		*i += 1;
		while (ft_isdigit(format[*i]))
		{
			syntax->precision = syntax->precision * 10 + (format[*i] - 48);
			*i += 1;
		}
	}
	if (format[*i] == '*')
	{
		syntax->precision = va_arg(args, int);
		*i += 1;
	}
	if (syntax->width < 0)
	{
		syntax->width = -syntax->width;
		if (!syntax->justify_left)
			syntax->justify_left = !syntax->justify_left;
	}
	if (syntax->precision < 0)
		syntax->precision_set = false;
	return (true);
}

int ft_printf(const char *format, ...)
{
	int	i;
	int len;
	va_list args;
	t_syntax syntax;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (ft_isascii(format[i]) && format[i] != '%')
		{
			write(1, &format[i++], 1);
			len++;
		}
		else if (format[i] == '%')
		{
			i++;
			extract_syntax(format, &i, &syntax, args);
			len += print_arg(format, &i, args, &syntax);
		}
	}
	va_end(args);
	return (len);
}

/*
int main(void)
{
	char *string = "salut yolo";
	// int	x = 214748364;
	// char c = 'x';
	int z;

	printf("TEST : \n");
	z = printf("%s", string);
	printf("\nretour : %d\n", z);
	return (0);
}
*/