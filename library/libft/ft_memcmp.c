/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:25:23 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/05 11:51:03 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	if (n < 1)
		return (0);
	while (str2[i] == str1[i])
	{
		if ((n - 1) == i)
		{
			return (0);
		}
		i++;
	}
	if (str1[i] != str2[i])
	{
		return (str1[i] - str2[i]);
	}
	else
		return (0);
}
