/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 15:10:05 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/16 18:27:48 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bool	initialize_syntax(t_syntax *syntax)
{
	syntax->justify_left = false;
	syntax->zeros = false;
	syntax->width = 0;
	syntax->precision = 0;
	syntax->precision_set = false;
	return (true);
}

int		extract_width(const char *format, int *i,
	t_syntax *syntax, va_list args)
{
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
	if (syntax->width < 0)
	{
		syntax->width = -syntax->width;
		if (!syntax->justify_left)
			syntax->justify_left = !syntax->justify_left;
	}
	return (1);
}

int		extract_precision(const char *format, int *i,
	t_syntax *syntax, va_list args)
{
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
	if (syntax->precision < 0)
		syntax->precision_set = false;
	return (1);
}

t_bool	extract_syntax(const char *format, int *i,
	t_syntax *syntax, va_list args)
{
	initialize_syntax(syntax);
	while (ft_strchr(FLAGS, format[*i]))
	{
		if (format[*i] == '0')
			syntax->zeros = true;
		else if (format[*i] == '-')
			syntax->justify_left = true;
		*i += 1;
	}
	extract_width(format, i, syntax, args);
	extract_precision(format, i, syntax, args);
	return (true);
}
