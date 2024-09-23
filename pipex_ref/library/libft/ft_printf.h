/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:48:52 by moni              #+#    #+#             */
/*   Updated: 2024/01/19 14:54:15 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
void	ft_putchar_print(char c, int *count);
void	ft_putnbr_hex_ptr(unsigned long nbr, int *count);
void	ft_putnbr_hex_xlo(unsigned int nb, int *count);
void	ft_putnbr_hex_xup(unsigned int nb, int *count);
void	ft_putnbr_u(unsigned int nb, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putptr(void *ptr, int *count);
void	ft_putstr(char *str, int *count);

#endif