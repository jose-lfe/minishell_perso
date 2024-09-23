/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:45:52 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/11/21 12:07:51 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	x;

	i = 0;
	x = (char) c;
	while (s[i] != '\0')
	{
		if (s[i] == x)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (s[i] == x)
	{
		return ((char *)(s + i));
	}
	return (NULL);
}
