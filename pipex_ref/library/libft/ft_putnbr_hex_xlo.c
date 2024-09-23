/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_xlo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:29:49 by moni              #+#    #+#             */
/*   Updated: 2024/01/19 14:54:15 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hex_xlo(unsigned int nb, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
		ft_putnbr_hex_xlo(nb / 16, count);
	ft_putchar_print(base[nb % 16], count);
}
