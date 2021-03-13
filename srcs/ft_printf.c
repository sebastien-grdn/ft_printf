/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:43:39 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/13 16:38:59 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(va_list args, t_syntax *syntax)
{
	int len;
	char *substring;
	char padding;
	int i;

	padding = ' ';
	if (syntax->zeros)
		padding = '0';
	substring = va_arg(args, char *);
	len = 0;
	while (substring[len])
		len++;
	if (syntax->precision_set && len > syntax->precision)
		len = syntax->precision;
	// printf("\nLEN : %d\n", len);
	i = len;
	while (syntax->width > i && !syntax->justify_left)
	{
		write(1, &padding, 1);
		i++;
	}
	if (syntax->precision_set && syntax->precision < len)
	{
		write(1, substring, syntax->precision);
		return (i - len + syntax->precision);
	}
	write(1, substring, len);
	while (syntax->width > i)
	{
		write(1, " ", 1);
		i++;
	}
	return (i);
}

int	print_char(va_list args, t_syntax *syntax)
{
	unsigned char c;
	int i;
	char padding;

	padding = ' ';
	if (syntax->zeros)
		padding = '0';
	i = 1;
	if (syntax->width < 0)
	{
		syntax->width = -syntax->width;
		syntax->justify_left = true;
	}
	while (syntax->width > i++ && !syntax->justify_left)
		write(1, &padding, 1);
	c = va_arg(args, int);
	write(1, &c, 1);
	while (syntax->width >= i++)
		write(1, " ", 1);
	if (syntax->width)
		return (syntax->width);
	return (1);
}

char		*ft_utoa(unsigned int n)
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

int padding_sign_precision(t_syntax *syntax, bool negative, int *len, char padding)
{
	int precision_length;
	int lol;

	lol = 0;
	precision_length = 0;
	while (syntax->precision_set && (*len + precision_length) < syntax->precision)
		precision_length++;
	if (negative && padding == '0')
		write(1, "-", 1);
	while (!syntax->justify_left && *len + precision_length < syntax->width)
	{
		write(1, &padding, 1);
		lol++;
		syntax->width--;
	}
	if (negative && padding == ' ')
		write(1, "-", 1);
	while (precision_length--)
	{
		write(1, "0", 1);
		*len = *len + 1;
	}
	return (lol);
}

int	print_unsigned(va_list args, t_syntax *syntax)
{
	int len;
	char *int_string;
	char padding;
	int lol;

	lol = 0;
	int_string = ft_utoa((unsigned int)va_arg(args, int));
	len = ft_strlen(int_string);
	padding = ' ';
	if (syntax->zeros && !syntax->precision_set)
		padding = '0';
	// printf("\nLEN 1 : %d\n", len);
	lol += padding_sign_precision(syntax, false, &len, padding);
	if (!(syntax->precision_set && syntax->precision == 0))
		write(1, int_string, ft_strlen(int_string));
	else
		len = 0;
	// printf("\nLEN 2 : %d\n", len);
	// printf("\nWIDTH : %d\n", syntax->width);
	while (len < syntax->width--)
	{
		write(1, &padding, 1);
		lol++;
	}
	return (len + lol);
}

char *handle_min_max()
{
	int i;
	char *return_string;

	if (!(return_string = malloc(sizeof(char) * (11))))
		return (NULL);
	i = -1;
	while (++i < 11)
		return_string[i] = "2147483648\0"[i];
	return return_string;
}

int	print_decimal(va_list args, t_syntax *syntax)
{
	int len;
	char *int_string;
	int input;
	char padding;
	int lol;
	bool negative;

	lol = 0;
	input = (int)va_arg(args, int);
	negative = false;
	if (input < 0)
	{
		negative = true;
		input = -input;
		lol++;
	}
	if (input == INT_MIN || input - 1 == INT_MAX)
		int_string = handle_min_max();
	else
		int_string = ft_itoa(input);
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
	return (len + lol);
}

void	to_upper_string(char *string)
{
	int i;

	i = -1;
	while (string[++i])
		string[i] = ft_toupper(string[i]);
	return ;
}

int	print_pointer(va_list args, t_syntax *syntax)
{
	unsigned long x;
	int			hexa_length;
	char *	hexa;
	unsigned long			y;
	int lol;
	char padding;
	int precision_length;

	x = (unsigned long) va_arg(args, void*);
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
	precision_length = 0;
	while (syntax->precision_set && (hexa_length + precision_length) < syntax->precision)
		precision_length++;
	padding = ' ';
	if (syntax->zeros && !syntax->precision_set)
		padding = '0';
	lol = precision_length;
	while (!syntax->justify_left && hexa_length + 2 < syntax->width)
	{
		write(1, &padding, 1);
		lol++;
		syntax->width--;
	}
	write(1, "0x", 2);
	while (precision_length--)
		write(1, "0", 1);
	write(1, hexa, hexa_length);
	while (lol + hexa_length + 2 < syntax->width)
	{
		write(1, &padding, 1);
		lol++;
	}
	return (2 + hexa_length + lol);
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
	//	printf("\nWIDTH %d\nLENGTH %d\n", syntax->width, hexa_length);
		write(1, &padding, 1);
		lol++;
		syntax->width--;
	}
	while (precision_length--)
		write(1, "0", 1);
	write(1, hexa, hexa_length);
	// while (syntax->precision_set && (hexa_length + precision_length) < syntax->precision)
	// 	precision_length++;
	// while (precision_length--)
	// 	write(1, "0", 1);
	free(hexa);
	while (lol + hexa_length < syntax->width)
	{
		write(1, &padding, 1);
		lol++;
	}
	return hexa_length + lol;
}

int print_modulo(t_syntax *syntax)
{
	int i;
	char padding;

	padding = ' ';
	if (syntax->zeros)
		padding = '0';
	i = 1;
	if (syntax->width < 0)
	{
		syntax->width = -syntax->width;
		syntax->justify_left = true;
	}
	while (syntax->width > i++ && !syntax->justify_left)
		write(1, &padding, 1);
	write(1, "%", 1);
	while (syntax->width >= i++)
		write(1, " ", 1);
	if (syntax->width)
		return (syntax->width);
	return (1);
}

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
	int	x = 214748364;
	char c = 'x';
	int z;

	printf("C\n");
	z = printf("char %c\n", c);
	printf("retour : %d\n", z);
	z = ft_printf("char %c\n", c);
	printf("retour : %d\n", z);

	printf("S\n");
	z = printf("string %s\n", string);
	printf("retour : %d\n", z);
	z = ft_printf("string %s\n", string);
	printf("retour : %d\n", z);

	printf("D\n");
	z = printf("int %d\n", x);
	printf("retour : %d\n", z);
	z = ft_printf("int %d\n", x);
	printf("retour : %d\n", z);
	printf("-----------------\n");
	z = printf("int %.*d\n", 8, x);
	printf("retour : %d\n", z);
	z = ft_printf("int %.*d\n", 8, x);
	printf("retour : %d\n", z);
	printf("-----------------\n");
	z = printf("int %8d\n", x);
	printf("retour : %d\n", z);
	z = ft_printf("int %8d\n", x);
	printf("retour : %d\n", z);
	printf("-----------------\n");
	z = printf("int %*d\n", 8, x);
	printf("retour : %d\n", z);
	z = ft_printf("int %*d\n", 8, x);
	printf("retour : %d\n", z);
	printf("-----------------\n");
	z = printf("int %0.8d\n", x);
	printf("retour : %d\n", z);
	z = ft_printf("int %0.8d\n", x);
	printf("retour : %d\n", z);
	printf("-----------------\n");
	z = printf("int %-.*d\n", 8, x);
	printf("retour : %d\n", z);
	z = ft_printf("int %-.*d\n", 8, x);
	printf("retour : %d\n", z);
	printf("-----------------\n");
	z = printf("int %.*d\n", 8, x);
	printf("retour : %d\n", z);
	z = ft_printf("int %.*d\n", 8, x);
	printf("retour : %d\n", z);

	printf("P\n");
	z = printf("pointer %p\n", &c);
	printf("retour : %d\n", z);
	z = ft_printf("pointer %p\n", &c);
	printf("retour : %d\n", z);

	printf("H\n");
	z = printf("hexa %X\n", x);
	printf("retour : %d\n", z);
	z = ft_printf("hexa %X\n", x);
	printf("retour : %d\n", z);
	return (0);
}
*/