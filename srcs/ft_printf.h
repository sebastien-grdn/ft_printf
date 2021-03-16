/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:28:17 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/16 18:29:31 by sg9031           ###   ########.fr       */
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
}	t_bool;

typedef struct	s_syntax {
	t_bool	justify_left;
	int		width;
	t_bool	zeros;
	t_bool	precision_set;
	int		precision;
}				t_syntax;

int				print_char(va_list args, t_syntax *syntax);
int				print_string(va_list args, t_syntax *syntax);
int				print_modulo(t_syntax *syntax);
int				print_hexa(va_list args, char flag, t_syntax *syntax);
int				print_pointer(va_list args, t_syntax *syntax);
int				print_unsigned(va_list args, t_syntax *syntax);
int				padding_sign_precision(t_syntax *syntax,
	t_bool negative, int *len, char padding);
int				print_decimal(va_list args, t_syntax *syntax);
t_bool			extract_syntax(const char *format, int *i,
	t_syntax *syntax, va_list args);
#endif
