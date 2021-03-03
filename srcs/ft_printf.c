/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:43:39 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/03 15:01:17 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_string(va_list args)
{
	int len;
	char *substring;
	substring = va_arg(args, char *);
	len = 0;
	while (substring[len])
		len++;
	write(1, substring, len);
	return ;
}

void	print_char(va_list args)
{
	char c;

	c = va_arg(args, int);
	write(1, &c, 1);
	return ;
}

void	print_decimal(va_list args, t_syntax *syntax)
{
	int len;
	char *int_string;
	char padding;

	int_string = ft_itoa((int)va_arg(args, int));
	len = 0;
	while (int_string[len])
		len++;
	padding = ' ';
	if (syntax->zeros)
		padding = '0';
	while (len < syntax->width--)
		write(1, &padding, 1);
	write(1, int_string, len);
	return ;
}

void	to_upper_string(char *string)
{
	int i;

	i = -1;
	while (string[++i])
		string[i] = ft_toupper(string[i]);
	return ;
}

void	print_pointer(va_list args, t_syntax *syntax)
{
	write(1, "[TODO]", 6);
	return ;
}

void	print_hexa(va_list args, char flag)
{
	int		x;
	int		y;
	int		hexa_length;
	char *	hexa;

	x = va_arg(args, int);
	y = x;
	hexa_length = 1;
	while (y/=16)
		hexa_length += 1;
	hexa = (char *)malloc(sizeof(char) * hexa_length + 1);
	hexa_length = 0;
	while (x >= 16)
	{
		hexa[hexa_length++] = ft_toupper("0123456789abcdef"[x / 16]);
		x %= 16;
	}
	hexa[hexa_length] = "0123456789abcdef"[x];
	hexa[hexa_length += 1] = '\0';
	if (flag == 'X')
		to_upper_string(hexa);
	write(1, hexa, hexa_length + 1);
	free(hexa);
	return ;
}

void	print_arg(const char *format, int *i, va_list args, t_syntax *syntax)
{
	if (format[*i] == 's')
		print_string(args);
	else if (format[*i] == 'd')
		print_decimal(args, syntax);
	else if (format[*i] == 'c')
		print_char(args);
	else if (format[*i] == 'p')
		print_pointer(args, syntax);
	else if (ft_strchr("xX", format[*i]))
		print_hexa(args, format[*i]);
	*i = *i + 1;
	return ;
}

bool initialize_syntax(t_syntax *syntax)
{
	syntax->justify_left = false;
	syntax->zeros = false;
	syntax->width = 0;
	return (true);
}

bool	extract_syntax(const char *format, int *i, t_syntax *syntax, va_list args)
{
	initialize_syntax(syntax);
	if (format[*i] == '0')
	{
		syntax->zeros = true;
		*i += 1;
	}
	while (!(ft_strchr(SPECIFIERS, format[*i])))
	{
		if (format[*i] == '-')
		{
			syntax->justify_left = true;
			*i += 1;
		}
		else if (format[*i] == '*')
		{
			syntax->width = va_arg(args, int);
			*i += 1;
		}
		else if (format[*i] == '.')
		{
			syntax->zeros = true;
			*i += 1;
		}
		else if (ft_isdigit(format[*i]))
			while (ft_isdigit(format[*i]))
			{
				syntax->width = syntax->width * 10 + (format[*i] - 48);
				*i += 1;
			}
		else
			*i += 1;
	}
	return (true);
}

int ft_printf(const char *format, ...)
{
	int	i;
	va_list args;
	t_syntax syntax;

	va_start(args, format);
	i = 0;
	while (format[i])
	{
		if (ft_isascii(format[i]) && format[i] != '%')
			write(1, &format[i++], 1);
		else if (format[i] == '%')
		{
			i++;
			extract_syntax(format, &i, &syntax, args);
			print_arg(format, &i, args, &syntax);
		}
	}
	va_end(args);
	return (0);
}


int main(void)
{
	char *string = "salut yolo";
	int	x = 154;
	char c = 'x';

	printf("C\n");
	printf("char %c\n", c);
	ft_printf("char %c\n", c);

	printf("S\n");
	printf("string %s\n", string);
	ft_printf("string %s\n", string);

	printf("D\n");
	printf("int %d\n", x);
	ft_printf("int %d\n", x);
	printf("-----------------\n");
	printf("int %.*d\n", 8, x);
	ft_printf("int %.*d\n", 8, x);
	printf("-----------------\n");
	printf("int %8d\n", x);
	ft_printf("int %8d\n", x);
	printf("-----------------\n");
	printf("int %*d\n", 8, x);
	ft_printf("int %*d\n", 8, x);
	printf("-----------------\n");
	printf("int %0.8d\n", x);
	ft_printf("int %0.8d\n", x);
	printf("-----------------\n");
	printf("int %-.*d\n", 8, x);
	ft_printf("int %-.*d\n", 8, x);
	printf("-----------------\n");
	printf("int %.*d\n", 8, x);
	ft_printf("int %.*d\n", 8, x);

	printf("P\n");
	printf("pointer %p\n", &c);
	ft_printf("pointer %p\n", &c);

	printf("H\n");
	printf("hexa %x\n", x);
	ft_printf("hexa %x\n", x);
	return (0);
}