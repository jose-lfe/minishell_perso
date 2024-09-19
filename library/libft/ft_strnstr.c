/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:42:49 by jose-lfe          #+#    #+#             */
/*   Updated: 2023/12/05 11:54:34 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[i] == '\0')
		return ((char *) haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (needle[0] == haystack[i])
		{
			while (needle[j] == haystack[i + j] && (i + j) < len)
			{
				j++;
				if (needle[j] == '\0')
					return ((char *) haystack + i);
			}
		}
		j = 0;
		i++;
	}
	return (0);
}
