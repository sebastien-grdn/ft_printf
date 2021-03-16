/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:31:09 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/16 18:27:31 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	padding_sign_precision(
	t_syntax *syntax, t_bool negative, int *len, char padding
)
{
	int precision_length;
	int lol;

	lol = 0;
	precision_length = 0;
	while (syntax->precision_set &&
		(*len + precision_length) < syntax->precision)
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
