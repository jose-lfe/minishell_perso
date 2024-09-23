/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:18:30 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/11/21 13:23:56 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	x;
	char	*r;

	i = 0;
	x = (char) c;
	r = NULL;
	while (s[i])
	{
		if (s[i] == x)
		{
			r = ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == x)
	{
		r = ((char *)(s + i));
	}
	return (r);
}
