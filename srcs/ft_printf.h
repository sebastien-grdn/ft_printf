/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 21:28:17 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/14 23:11:58 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# define SPECIFIERS "cspdiuxX%"
# define FLAGS "-0.*"

// À VIRER 
# include <stdio.h>

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

#endif