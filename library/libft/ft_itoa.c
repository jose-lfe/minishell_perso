/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:11:06 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/11/29 14:18:42 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// max int : 2147483647, min int : -2147483648

#include "libft.h"

static char	*ft_neg(void);
static int	ft_size(int n, int neg);
static void	ft_fill(int n, int neg, int size, char *res);

char	*ft_itoa(int n)
{
	char	*res;
	int		neg;
	int		size;

	neg = 0;
	if (n == -2147483648)
		return (ft_neg());
	if (n < 0)
	{
		neg = 1;
		n = n * -1;
	}
	size = ft_size(n, neg);
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_fill(n, neg, size, res);
	return (res);
}

static char	*ft_neg(void)
{
	char	*res;

	res = malloc(12 * sizeof(char));
	if (!res)
		return (NULL);
	res[0] = '-';
	res[1] = '2';
	res[2] = '1';
	res[3] = '4';
	res[4] = '7';
	res[5] = '4';
	res[6] = '8';
	res[7] = '3';
	res[8] = '6';
	res[9] = '4';
	res[10] = '8';
	res[11] = '\0';
	return (res);
}

static int	ft_size(int n, int neg)
{
	int	size;

	size = 1;
	while (n / 10 > 0)
	{
		size++;
		n = n / 10;
	}
	return (size + neg);
}

static void	ft_fill(int n, int neg, int size, char *res)
{
	res[size] = '\0';
	size--;
	while (n / 10 > 0)
	{
		res[size] = n % 10 + '0';
		n = n / 10;
		size--;
	}
	res[size] = n + '0';
	if (neg == 1)
		res[0] = '-';
}
