/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:28:17 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/15 15:28:43 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# define SPECIFIERS "cspdiuxX%"
# define FLAGS "-0"

typedef enum {
	false,
	true
} bool;

typedef struct s_syntax {
	bool	justify_left;
	int		width;
	bool	zeros;
	bool	precision_set;
	int		precision;
} t_syntax;

int	print_char(va_list args, t_syntax *syntax);
int	print_string(va_list args, t_syntax *syntax);
int print_modulo(t_syntax *syntax);
int	print_hexa(va_list args, char flag, t_syntax *syntax);
int	print_pointer(va_list args, t_syntax *syntax);
int	print_unsigned(va_list args, t_syntax *syntax);
int padding_sign_precision(t_syntax *syntax, bool negative, int *len, char padding);
int	print_decimal(va_list args, t_syntax *syntax);
bool	extract_syntax(const char *format, int *i, t_syntax *syntax, va_list args);
#endif