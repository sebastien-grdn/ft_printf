/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modulo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 11:19:38 by sg9031            #+#    #+#             */
/*   Updated: 2021/03/15 16:09:15 by sg9031           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_modulo(t_syntax *syntax)
{
	int		i;
	char	padding;

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
