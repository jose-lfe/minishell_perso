/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:11:10 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/06 12:54:47 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	nc;
	size_t			i;

	str = (unsigned char *) s;
	nc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == nc)
		{
			return ((void *)(str + i));
		}
		i++;
	}
	return (NULL);
}
